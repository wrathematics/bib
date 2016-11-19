#include "../cdefs.h"
#include "../types.h"
#include "../misc/safeomp.h"

double bib_trace(cmat_r x)
{
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  double tr = 0.0;
  
  SAFE_FOR_SIMD
  for (len_t i=0; i<MIN(m, n); i+=(m+1))
    tr += DATA(x)[i + n*i];
  
  return tr;
}
