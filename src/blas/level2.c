#include <stdlib.h>

#include "blas.h"

#include "../bib.h"
#include "../cdefs.h"

#define BLOCKSIZE 8 // TODO check cache line explicitly


// Copy lower triangle to upper
static inline void symmetrize(const len_t n, double *restrict x)
{
  // #pragma omp parallel for default(none) shared(x) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
  for (len_t j=0; j<n; j+=BLOCKSIZE)
  {
    for (len_t i=j+1; i<n; i+=BLOCKSIZE)
    {
      for (len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (len_t row=i; row<i+BLOCKSIZE && row<n; ++row)
          x[col + n*row] = x[row + n*col];
      }
    }
  }
}

// upper triangle of t(x) %*% x
int bib_crossprod(const double alpha, cmat_r x, mat_r cp)
{
  CHECKIFSAME(x, cp);
  int info = 0;
  if (NROWS(cp) != NCOLS(x) || NCOLS(cp) != NCOLS(x))
    return LIBBIB_RETDIMMISMATCH;
  
  dsyrk_(&(char){'l'}, &(char){'t'}, &NCOLS(x), &NROWS(x), &alpha, DATA(x),
    &NROWS(x), &(double){0.0}, DATA(cp), &NCOLS(x));
  
  symmetrize(NROWS(cp), DATA(cp));
  
  return info;
}

int bib_crossprod_a(const double alpha, cmat_r x, dmatrix_t **cp)
{
  *cp = newmat(NCOLS(x), NCOLS(x));
  CHECKMALLOC(*cp);
  
  return bib_crossprod(alpha, x, *cp);
}



int bib_tcrossprod(const double alpha, cmat_r x, mat_r tcp)
{
  CHECKIFSAME(x, tcp);
  int info = 0;
  if (NROWS(tcp) != NROWS(x) || NCOLS(tcp) != NROWS(x))
    return LIBBIB_RETDIMMISMATCH;
  
  dsyrk_(&(char){'l'}, &(char){'n'}, &NROWS(x), &NCOLS(x), &alpha, DATA(x),
    &NROWS(x), &(double){0.0}, DATA(tcp), &NROWS(x));
    
  symmetrize(NROWS(tcp), DATA(tcp));
  
  return info;
}

int bib_tcrossprod_a(const double alpha, cmat_r x, dmatrix_t **tcp)
{
  *tcp = newmat(NROWS(x), NROWS(x));
  CHECKMALLOC(*tcp);
  
  return bib_tcrossprod(alpha, x, *tcp);
}



// ret = alpha*x*y
int bib_mvprod(const bool trans, const double alpha, cmat_r x, cvec_r y, vec_r ret)
{
  CHECKIFSAME(y, ret);
  char t;
  if (trans)
  {
    if (LENGTH(y) != NROWS(x))
      return LIBBIB_INDIMMISMATCH;
    else if (LENGTH(ret) != NCOLS(x))
      return LIBBIB_RETDIMMISMATCH;
    
    t = 'T';
  }
  else
  {
    if (LENGTH(y) != NCOLS(x))
      return LIBBIB_INDIMMISMATCH;
    else if (LENGTH(ret) != NROWS(x))
      return LIBBIB_RETDIMMISMATCH;
    
    t = 'N';
  }
  
  dgemv_(&t, &NROWS(x), &NCOLS(x), &alpha, DATA(x), &NROWS(x), DATA(y), 
    &(int){1}, &(double){0.0}, DATA(ret), &(int){1});
  
  return LIBBIB_OK;
}

int bib_mvprod_a(const bool trans, const double alpha, cmat_r x, cvec_r y, dvector_t **ret)
{
  len_t len;
  if (trans)
    len = NCOLS(x);
  else
    len = NROWS(x);
  
  *ret = newvec(len);
  CHECKMALLOC(*ret);
  
  return bib_mvprod(trans, alpha, x, y, *ret);
}
