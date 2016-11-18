#include "../types.h"
#include "safeomp.h"


void vrev(vec_r x)
{
  len_t j = x->len-1;
  double *const x_data = x->data;
  
  SAFE_FOR_SIMD
  for (len_t i=0; i<x->len/2; i++)
  {
    const double tmp = x_data[i];
    x_data[i] = x_data[j];
    x_data[j] = tmp;
    j--;
  }
}



void mrev(mat_r x)
{
  const len_t m = x->nrows;
  const len_t n = x->ncols;
  double *const x_data = x->data;
  len_t last = n - 1;
  
  for (len_t j=0; j<n/2; j++)
  {
    #pragma omp parallel for if(m>1000)
    for (len_t i=0; i<m; i++)
    {
      const double tmp = x_data[i + m*j];
      x_data[i + m*j] = x_data[i + m*last];
      x_data[i + m*last] = tmp;
    }
    
    last--;
  }
}
