#include <stdlib.h>
#include <errno.h>

#include "lapack.h"
#include "../bib.h"
#include "../cdefs.h"
#include "../types.h"


int bib_lu(mat_r x, ivec_r pivot)
{
  int ret = LIBBIB_OK;
  int info;
  const int m = NROWS(x);
  const int n = NCOLS(x);
  
  dgetrf_(&m, &n, DATA(x), &m, DATA(pivot), &info);
  if (info != 0)
  {
    errno = info;
    ret = LIBBIB_LAPACKERR;
  }
  
  return ret;
}

int bib_lu_a(mat_r x, ivector_t **pivot)
{
  const int m = NROWS(x);
  const int n = NCOLS(x);
  
  *pivot = newivec(MIN(m, n));
  if (DATA(*pivot) == NULL)
    return LIBBIB_BADMALLOC;
  
  return bib_lu(x, *pivot);
}



int bib_det(mat_r x, double *det)
{
  int ret;
  ivector_t *pivot;
  const int n = NROWS(x);
  if (n != NCOLS(x))
    return LIBBIB_NONSQUARE;
  
  ret = bib_lu_a(x, &pivot);
  CHECKRET(ret);
  
  *det = 1.0;
  for (int i=0; i<n; i++)
    *det *= DATA(x)[i + n*i];
  
  freeivec(pivot);
  
  return ret;
}



int bib_invert(mat_r x)
{
  const int n = NROWS(x);
  if (n != NCOLS(x))
    return LIBBIB_NONSQUARE;
  
  double *const x_data = x->data;
  int info = LIBBIB_OK;
  int *ipiv;
  int lwork;
  double tmp;
  double *work;
  
  
  // Factor x = LU
  ipiv = malloc(n * sizeof(*ipiv));
  if (ipiv == NULL)
    return LIBBIB_BADMALLOC;
  
  dgetrf_(&n, &n, x_data, &n, ipiv, &info);
  if (info != 0)
  {
    errno = info;
    info = LIBBIB_LAPACKERR;
    goto cleanup;
  }
  
  // Invert
  lwork = -1;
  dgetri_(&n, x_data, &n, ipiv, &tmp, &lwork, &info);
  if (info != 0)
  {
    errno = info;
    info = LIBBIB_LAPACKERR;
    goto cleanup;
  }
  
  lwork = (int) tmp;
  work = malloc(lwork * sizeof(*work));
  if (work == NULL)
  {
    free(ipiv);
    return LIBBIB_BADMALLOC;
  }
  
  dgetri_(&n, x_data, &n, ipiv, work, &lwork, &info);
  
  
  free(work);
cleanup:
  free(ipiv);
  
  return info;
}
