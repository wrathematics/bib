#include <stdlib.h>

#include "../cdefs.h"
#include "../types.h"


static inline int _bib_allocator_dbl(clen_t len, double **data)
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

static inline int _bib_allocator_int(clen_t len, int **data)
{
  if (*data != NULL)
  {
    int *tmp = realloc(*data, len  * sizeof(**data));
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



dvector_t *newvec(clen_t len)
{
  double *data = NULL;
  dvector_t *ret = malloc(sizeof(*ret));
  if (ret == NULL)
    return NULL;
  
  int check = _bib_allocator_dbl(len, &data);
  if (check != LIBBIB_OK)
  {
    free(ret);
    return NULL;
  }
  
  LENGTH(ret) = len;
  DATA(ret) = data;
  
  return ret;
}

int setvec(clen_t len, double *data, dvector_t *v)
{
  if (data == NULL)
  {
    int check = _bib_allocator_dbl(len, &data);
    if (check != LIBBIB_OK)
      return check;
  }
  
  LENGTH(v) = len;
  DATA(v) = data;
  return LIBBIB_OK;
}



ivector_t *newivec(clen_t len)
{
  int *data = NULL;
  ivector_t *ret = malloc(sizeof(*ret));
  if (ret == NULL)
    return NULL;
  
  int check = _bib_allocator_int(len, &data);
  if (check != LIBBIB_OK)
  {
    free(ret);
    return NULL;
  }
  
  LENGTH(ret) = len;
  DATA(ret) = data;
  
  return ret;
}



dmatrix_t *newmat(clen_t nrows, clen_t ncols)
{
  double *data = NULL;
  dmatrix_t *ret = malloc(sizeof(*ret));
  if (ret == NULL)
    return NULL;
  
  NROWS(ret) = nrows;
  NCOLS(ret) = ncols;
  int check = _bib_allocator_dbl(nrows*ncols, &data);
  if (check != LIBBIB_OK)
  {
    free(ret);
    return NULL;
  }
  
  DATA(ret) = data;
  
  return ret;
}

int setmat(clen_t nrows, clen_t ncols, double *data, dmatrix_t *m)
{
  if (data == NULL)
  {
    int check = _bib_allocator_dbl(nrows*ncols, &data);
    if (check != LIBBIB_OK)
      return check;
  }
  
  NROWS(m) = nrows;
  NCOLS(m) = ncols;
  DATA(m) = data;
  return LIBBIB_OK;
}



void freevec(dvector_t *v)
{
  free(DATA(v));
  DATA(v) = NULL;
  LENGTH(v) = 0;
  free(v);
  v = NULL;
}

void freeivec(ivector_t *v)
{
  free(DATA(v));
  DATA(v) = NULL;
  LENGTH(v) = 0;
  free(v);
  v = NULL;
}

void freemat(dmatrix_t *m)
{
  free(DATA(m));
  DATA(m) = NULL;
  NROWS(m) = 0;
  NCOLS(m) = 0;
  free(m);
  m = NULL;
}
