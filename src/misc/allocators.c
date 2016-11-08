#include <stdlib.h>

#include "../cdefs.h"
#include "../types.h"


static inline int _bib_allocator(clen_t len, double **data)
{
  if (*data != NULL)
  {
    double *tmp = realloc(*data, len  * sizeof(**data));
    if (tmp == NULL)
    {
      // FIXME leave it for the user?
      // free(*data);
      return LIBBIB_BADMALLOC;
    }
    else
      *data = tmp;
  }
  else
  {
    *data = malloc(len * sizeof(**data));
    CHECKMALLOC(data);
  }
  
  return LIBBIB_OK;
}



dvector_t *newvec(clen_t len, double *data)
{
  dvector_t *ret = malloc(sizeof(*ret));
  ret->len = len;
  int check = _bib_allocator(len, &data);
  // if (check != LIBBIB_OK)
    // TODO
  
  ret->data = data;
  
  return ret;
}

int setvec(clen_t len, double *data, dvector_t *v)
{
  if (data == NULL)
    _bib_allocator(len, &data);
  
  v->len = len;
  v->data = data;
  return LIBBIB_OK;
}



dmatrix_t *newmat(clen_t nrows, clen_t ncols, double *data)
{
  dmatrix_t *ret = malloc(sizeof(*ret));
  ret->nrows = nrows;
  ret->ncols = ncols;
  int check = _bib_allocator(nrows*ncols, &data);
  // if (check != LIBBIB_OK)
    // TODO
  
  ret->data = data;
  
  return ret;
}

int setmat(clen_t nrows, clen_t ncols, double *data, dmatrix_t *m)
{
  if (data == NULL)
    _bib_allocator(nrows*ncols, &data);
  
  m->nrows = nrows;
  m->ncols = ncols;
  m->data = data;
  return LIBBIB_OK;
}
