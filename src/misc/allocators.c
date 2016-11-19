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
  
  LENGTH(ret) = len;
  DATA(ret) = data;
  
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
  
  LENGTH(v) = len;
  DATA(v) = data;
  return LIBBIB_OK;
}



dmatrix_t *newmat(clen_t nrows, clen_t ncols, double *data)
{
  dmatrix_t *ret = malloc(sizeof(*ret));
  if (ret == NULL)
    return NULL;
  
  NROWS(ret) = nrows;
  NCOLS(ret) = ncols;
  int check = _bib_allocator(nrows*ncols, &data);
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
    int check = _bib_allocator(nrows*ncols, &data);
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
}

void freemat(dmatrix_t *m)
{
  free(DATA(m));
  DATA(m) = NULL;
  NROWS(m) = 0;
  NCOLS(m) = 0;
}
