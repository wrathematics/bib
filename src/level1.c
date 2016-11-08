#include <math.h>

#include "blas.h"
#include "cdefs.h"
#include "types.h"


// C ddot replica using dgemm
double dotprod(cvec_r x, cvec_r y)
{
  // TODO len check
  double dp;
  
  dgemm_(&(char){'t'}, &(char){'n'}, &(int){1}, &(int){1}, &x->len,
    &(double){1.0}, x->data, &x->len, y->data, &x->len, &(double){0.0}, &dp,
    &(int){1});
  
  return dp;
}



static inline double dnrm2(int n, double *restrict x, int incx)
{
  double norm, scale, ssq;
  
  if (n < 1 || incx < 1)
    norm = 0.;
  else if (n == 1)
    norm = fabs(x[0]);
  else
  {
    scale = 0.;
    ssq = 1.;
    
    dlassq_(&n, x, &incx, &scale, &ssq);
    norm = scale * sqrt(ssq);
  }
  
  return norm;
}

double vnorm(cvec_r x)
{
  return dnrm2(x->len, x->data, 0);
}



int vswap(cvec_r x, vec_r y)
{
  if (x->len != y->len)
    return LIBBIB_INDIMMISMATCH;
  
  dswap_(&x->len, x->data, &(int){0}, y->data, &(int){0});
  
  return LIBBIB_OK;
}



int vcopy(cvec_r x, vec_r y)
{
  if (x->len != y->len)
    return LIBBIB_INDIMMISMATCH;
  
  dcopy_(&x->len, x->data, &(int){0}, y->data, &(int){0});
  
  return LIBBIB_OK;
}



void vscale(const double alpha, vec_r x)
{
  dscal_(&x->len, &alpha, x->data, &(int){0});
}
