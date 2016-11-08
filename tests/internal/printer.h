#ifndef __INTERNAL_PRINTER_H__
#define __INTERNAL_PRINTER_H__

#include <stdio.h>
#include "../../src/types.h"

static inline void matprinter(const int m, const int n, const double *const restrict x)
{
  int i, j;
  
  for (i=0; i<m; i++)
  {
    for (j=0; j<n; j++)
      printf("%.2f ", x[i+m*j]);
    
    putchar('\n');
  }
  
  putchar('\n');
}

static inline void printmat(dmatrix_t *mat)
{
  const int m = mat->nrows;
  const int n = mat->ncols;
  const double *x = mat->data;
  
  matprinter(m, n, x);
}

static inline void printvec(dvector_t *vec)
{
  const int len = vec->len;
  const double *x = vec->data;
  
  matprinter(1, len, x);
}

#endif
