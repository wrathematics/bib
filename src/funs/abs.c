#include <math.h>
#include "../cdefs.h"
#include "../types.h"
#include "../misc/safeomp.h"

void bib_mabs(mat_r x)
{
  const int m = NROWS(x);
  const int n = NCOLS(x);
  
  #pragma omp parallel for if(m*n > OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    SAFE_SIMD
    for (int i=0; i<m; i++)
      DATA(x)[i + n*j] = fabs(DATA(x)[i + n*j]);
  }
}
