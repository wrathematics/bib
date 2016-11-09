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
  if (ret == NULL)
    return NULL;
  
  int check = _bib_allocator(len, &data);
  if (check != LIBBIB_OK)
  {
    free(ret);
    return NULL;
  }
  
  ret->len = len;
  ret->data = data;
  
  return ret;
}

int setvec(clen_t len, double *data, dvector_t *v)
{
  if (data == NULL)
  {
    int check = _bib_allocator(len, &data);
    if (check != LIBBIB_OK)
      return check;
  }
  
  v->len = len;
  v->data = data;
  return LIBBIB_OK;
}



dmatrix_t *newmat(clen_t nrows, clen_t ncols, double *data)
{
  dmatrix_t *ret = malloc(sizeof(*ret));
  if (ret == NULL)
    return NULL;
  
  ret->nrows = nrows;
  ret->ncols = ncols;
  int check = _bib_allocator(nrows*ncols, &data);
  if (check != LIBBIB_OK)
  {
    free(ret);
    return NULL;
  }
  
  ret->data = data;
  
  return ret;
}

int setmat(clen_t nrows, clen_t ncols, double *data, dmatrix_t *m)
{
  if (data == NULL)
  {
    int check = _bib_allocator(nrows*ncols, &data);
    if (check != LIBBIB_OK)
      return check;
  }
  
  m->nrows = nrows;
  m->ncols = ncols;
  m->data = data;
  return LIBBIB_OK;
}



void freevec(dvector_t *v)
{
  free(v->data);
  v->data = NULL;
  v->len = 0;
}

void freemat(dmatrix_t *m)
{
  free(m->data);
  m->data = NULL;
  m->nrows = 0;
  m->ncols = 0;
}
