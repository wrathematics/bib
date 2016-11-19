#include <math.h>

#include "blas.h"
#include "../cdefs.h"
#include "../types.h"


// C ddot replica using dgemm
double bib_dotprod(cvec_r x, cvec_r y)
{
  if (LENGTH(x) != LENGTH(y))
    return LIBBIB_INDIMMISMATCH;
  
  double dp;
  
  dgemm_(&(char){'t'}, &(char){'n'}, &(int){1}, &(int){1}, &LENGTH(x),
    &(double){1.0}, DATA(x), &LENGTH(x), DATA(y), &LENGTH(x), &(double){0.0},
    &dp, &(int){1});
  
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

double bib_vnorm(cvec_r x)
{
  return dnrm2(LENGTH(x), DATA(x), 1);
}



int bib_vswap(cvec_r x, vec_r y)
{
  CHECKIFSAME(x, y);
  if (LENGTH(x) != LENGTH(y))
    return LIBBIB_INDIMMISMATCH;
  
  dswap_(&LENGTH(x), DATA(x), &(int){1}, DATA(y), &(int){1});
  
  return LIBBIB_OK;
}



int bib_vcopy(cvec_r x, vec_r y)
{
  CHECKIFSAME(x, y);
  if (LENGTH(x) != LENGTH(y))
    return LIBBIB_INDIMMISMATCH;
  
  dcopy_(&LENGTH(x), DATA(x), &(int){1}, DATA(y), &(int){1});
  
  return LIBBIB_OK;
}



int bib_vscale(const double alpha, vec_r x)
{
  dscal_(&LENGTH(x), &alpha, DATA(x), &(int){1});
  return LIBBIB_OK;
}
