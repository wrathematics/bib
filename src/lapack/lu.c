#include <stdlib.h>

#include "lapack.h"
#include "../cdefs.h"
#include "../types.h"


int invert(mat_r x, int *info)
{
  const int n = x->nrows;
  if (n != x->ncols)
    return LIBBIB_NONSQUARE;
  
  double *const x_data = x->data;
  
  int *ipiv;
  int lwork;
  double tmp;
  double *work;
  
  
  // Factor x = LU
  ipiv = malloc(n * sizeof(*ipiv));
  if (ipiv == NULL)
    return LIBBIB_BADMALLOC;
  
  dgetrf_(&n, &n, x_data, &n, ipiv, info);
  if (*info != 0)
    goto cleanup;
  
  // Invert
  lwork = -1;
  dgetri_(&n, x_data, &n, ipiv, &tmp, &lwork, info);
  if (info != 0)
    goto cleanup;
  
  lwork = (int) tmp;
  work = malloc(lwork * sizeof(*work));
  if (work == NULL)
  {
    free(ipiv);
    return LIBBIB_BADMALLOC;
  }
  
  dgetri_(&n, x_data, &n, ipiv, work, &lwork, info);
  
  
  free(work);
cleanup:
  free(ipiv);
  
  return LIBBIB_OK;
}
