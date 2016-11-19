#include <math.h>
#include "../cdefs.h"
#include "../types.h"
#include "../misc/safeomp.h"

static inline double find_min(clenprod_t len, const double *const x)
{
  double min = x[0];
  for (lenprod_t i=1; i<len; i++)
  {
    if (x[i] < min)
      min = x[i];
  }
  
  return min;
}

static inline double find_max(clenprod_t len, const double *const x)
{
  double max = x[0];
  for (lenprod_t i=1; i<len; i++)
  {
    if (x[i] > max)
      max = x[i];
  }
  
  return max;
}



double bib_vmin(cvec_r x)
{
  return find_min(LENGTH(x), DATA(x));
}

double bib_mmin(cmat_r x)
{
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  return find_min(m*n, DATA(x));
}



double bib_vmax(cvec_r x)
{
  return find_max(LENGTH(x), DATA(x));
}

double bib_mmax(cmat_r x)
{
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  return find_max(m*n, DATA(x));
}
