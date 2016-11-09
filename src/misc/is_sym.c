#include <math.h>
#include <float.h>

#include "../types.h"
#define BLOCKSIZE 16

#define EPS 1000*FLT_EPSILON


static inline bool samenum(const double x, const double y)
{
  return (fabs(x-y) < EPS);
}

bool is_sym(cmat_r x)
{
  const int n = x->nrows;
  if (n != x->ncols)
    return false;
  
  const double * const x_data = x->data;
  
  for (int j=0; j<n; j+=BLOCKSIZE)
  {
    for (int i=j; i<n; i+=BLOCKSIZE)
    {
      for (int col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (int row=i; row<i+BLOCKSIZE && row<n; ++row)
        {
          const bool check = samenum(x_data[col + n*row], x_data[row + n*col]);
          if (!check)
            return false;
        }
      }
    }
  }
  
  return true;
}
