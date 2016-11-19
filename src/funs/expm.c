/* Matrix exponentiation algorithm from:
   "New Scaling and Squaring Algorithm for the Matrix Exponential", by
   Awad H. Al-Mohy and Nicholas J. Higham, August 2009
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../blas/blas.h"
#include "../lapack/lapack.h"

#include "../bib.h"
#include "../cdefs.h"
#include "../types.h"

#define SGNEXP(x,pow) (x==0?(pow==0?1:0):(x>0?1:(pow%2==0?1:(-1))))


// Pade' Coefficients for p==q==13

// Generated from bc via:
// scale=50
// define f(x) {
// if (x <= 1) return (1);
// return (x*f(x-1));
// }
// m=13
// for(j=0; j<=m; j++) {f(2*m-j)*f(m)/f(2*m)/f(m-j)/f(j);}
const double matexp_pade_coefs[14] =
{
  1.0,
  0.5,
  0.12,
  1.833333333333333333333e-2,
  1.992753623188405797101e-3,
  1.630434782608695652174e-4,
  1.035196687370600414079e-5,
  5.175983436853002070393e-7,
  2.043151356652500817261e-8,
  6.306022705717595115002e-10,
  1.483770048404140027059e-11,
  2.529153491597965955215e-13,
  2.810170546219962172461e-15,
  1.544049750670308885967e-17
};



// -------------------------------------------------------- 
// Utilities
// -------------------------------------------------------- 

// C = A * B for square matrices
static void matprod(int n, double *restrict a, double *restrict b, double *restrict c)
{
  char trans = 'N';
  double one = 1.0, zero = 0.0;
  
  dgemm_(&trans, &trans, &n, &n, &n, &one, a, &n, b, &n, &zero, c, &n);
}



// Copy A ONTO B, i.e. B = A
static inline void matcopy(int n, double *restrict A, double *restrict B)
{
  char uplo = 'A';
  
  dlacpy_(&uplo, &n, &n, A, &n, B, &n);
}



// Identity matrix
static inline void mateye(const unsigned int n, double *a)
{
  int i;
  
  for (i=0; i<n*n; i++)
    a[i] = 0.0;
  
  i = 0;
  while (i < n*n)
  {
    a[i] = 1.0;
    i += n+1;
  }
}



// 1-norm for a square matrix
static double matnorm_1(const double *x, const int n)
{
  int i, j;
  double norm = 0;
  double tmp;
  
  // max(colSums(abs(x))) 
  for (j=0; j<n; j++)
  {
    tmp = 0;
    
    for (i=0; i<n; i++)
      tmp += fabs(x[i + j*n]);
    
    if (tmp > norm)
      norm = tmp;
  }
  
  return norm;
}



#define NTHETA 5

static int matexp_scale_factor(const double *x, const int n)
{
  int i;
  const double theta[] = {1.5e-2, 2.5e-1, 9.5e-1, 2.1e0, 5.4e0};
  
  const double x_1 = matnorm_1(x, n);
  
  for (i=0; i<NTHETA; i++)
  {
    if (x_1 <= theta[i])
      return 0;
  }
  
  i = (int) ceil(log2(x_1/theta[4]));
  
  return 1 << i;
}



// Matrix power by squaring: P = A^b (A is garbage on exit)
static void matpow_by_squaring(double *restrict A, int n, int b, double *restrict P)
{
  double *TMP;
  
  mateye(n, P);
  
  // Trivial cases
  if (b == 0)
    return;
  
  if (b == 1)
  {
    matcopy(n, A, P);
    return;
  }
  
  
  // General case
  TMP = malloc(n*n*sizeof(double));
  
  while (b)
  {
    if (b&1)
    {
      matprod(n, P, A, TMP);
      matcopy(n, TMP, P);
    }
    
    b >>= 1;
    matprod(n, A, A, TMP);
    matcopy(n, TMP, A);
  }
  
  free(TMP);
}



// -------------------------------------------------------- 
// Matrix Exponentiation via Pade' Approximations
// -------------------------------------------------------- 

/* r_m(x) = p_m(x) / q_m(x), where
   p_m(x) = sum_{j=0}^m (2m-j)!m!/(2m)!/(m-j)!/j! * x^j
  
   and q_m(x) = p_m(-x)
*/

// Workhorse for matexp_pade
void matexp_pade_fillmats(const int m, const int n, const int i, double *restrict N, double *restrict D, double *restrict B, const double *restrict C)
{
  int j;
  const double tmp = matexp_pade_coefs[i];
  double tmpj;
  const int sgn = SGNEXP(-1, i);
  
    /* Performs the following actions:
        B = C
        N = pade_coef[i] * C
        D = (-1)^j * pade_coef[i] * C
    */
    for (j=0; j<m*n; j++)
    {
      tmpj = C[j];
      B[j] = tmpj;
      
      tmpj *= tmp;
      
      N[j] += tmpj;
      D[j] += sgn*tmpj;
    }
}



// Exponentiation via Pade' expansion
static void matexp_pade(int n, const int p, double *restrict A, double *restrict N)
{
  int i, info = 0;
  int *ipiv;
  double *B, *C, *D;
  
  // Power of A
  B = calloc(n*n, sizeof(*B));
  assert(B != NULL);
  
  // Temporary storage for matrix multiplication
  C = calloc(n*n, sizeof(*C));
  assert(C != NULL);
  
  D = calloc(n*n, sizeof(*D));
  assert(D != NULL);
  
  matcopy(n, A, C);
  
  i = 0;
  while (i < n*n)
  {
    N[i] = 1.0;
    D[i] = 1.0;
    
    i += n+1;
  }
  
  
  // Fill N and D
  for (i=1; i<=p; i++)
  {
    // C = A*B
    if (i > 1)
      matprod(n, A, B, C);
    
    // Update matrices
    matexp_pade_fillmats(n, n, i, N, D, B, C);
  }
  
  // R <- inverse(D) %*% N
  ipiv = calloc(n, sizeof(*ipiv));
  assert(ipiv != NULL);
  
  dgesv_(&n, &n, D, &n, ipiv, N, &n, &info);
  
  
  free(B);
  free(C);
  free(D);
  free(ipiv);
}



/*
  n       Number of rows/cols of (square) matrix x.
  
  p       Order of the Pade' approximation. 0 < p <= 13.
  
  t       Scaling factor for x (t=1 canonical).
  
  x       Input (square) matrix.  On function exit, the values
          in x are garbage.
  
  ret     On exit, ret = expm(x).
*/

static void matexp(int n, const int p, double *restrict x, double *restrict ret)
{
  int m;
  int nn = n*n;
  int one = 1;
  double tmp;
  
  m = matexp_scale_factor(x, n);
  
  if (m == 0)
    matexp_pade(n, p, x, ret);
  else
  {
    tmp = 1. / ((double) m);
    dscal_(&nn, &tmp, x, &one);
  
    matexp_pade(n, p, x, ret);
  
    matcopy(n, ret, x);
  
    matpow_by_squaring(x, n, m, ret);
  }
}



int bib_mexp(const int p, mat_r x, mat_r ret)
{
  if (NROWS(x) != NCOLS(x))
    return LIBBIB_NONSQUARE;
  
  matexp(NROWS(x), p, DATA(x), DATA(ret));
  
  return LIBBIB_OK;
}

int bib_mexp_a(const int p, mat_r x, dmatrix_t **ret)
{
  if (NROWS(x) != NCOLS(x))
    return LIBBIB_NONSQUARE;
  
  *ret = newmat(NROWS(x), NROWS(x));
  CHECKMALLOC(*ret);
  
  return bib_mexp(p, x, *ret);
}
