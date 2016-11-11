#include "lapack.h"
#include "../cdefs.h"
#include "../bib.h"


void mcopy(cmat_r x, mat_r y)
{
  char uplo = 'a';
  dlacpy_(&uplo, &x->nrows, &x->ncols, x->data, &x->nrows, y->data, &y->nrows);
}

int mcopy_a(cmat_r x, dmatrix_t **restrict y)
{
  double *data = NULL;
  *y = newmat(x->nrows, x->ncols, data);
  if (data == NULL)
    return LIBBIB_BADMALLOC;
  
  mcopy(x, *y);
  
  return LIBBIB_OK;
}
