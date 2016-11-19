#include "blas.h"

#include "../bib.h"
#include "../types.h"
#include "../cdefs.h"


int bib_mmprod(const bool transx, const bool transy, cmat_r x, cmat_r y, mat_r ret)
{
  CHECKIFSAME(x, ret);
  CHECKIFSAME(y, ret);
  
  // m = # rows of op(x)
  // n = # cols of op(y)
  // k = # cols of op(x)
  len_t im, in, ik;
  char ctransx, ctransy;
  
  
  if (transy)
    ctransy = 'T';
  else
    ctransy = 'N';
  
  if (transx)
  {
    ctransx = 'T';
    
    im = NCOLS(x);
    ik = NROWS(x);
    
    if (transy)
      in = NROWS(y);
    else
      in = NCOLS(y);
  }
  else
  {
    ctransx = 'N';
    
    im = NROWS(x);
    ik = NCOLS(x);
    
    if (transy)
      in = NROWS(y);
    else
      in = NCOLS(y);
  }
  
  // TODO check for conformality
  
  dgemm_(&ctransx, &ctransy, &im, &in, &ik, &(double){1.0}, DATA(x), &NROWS(x), DATA(y), &NROWS(y), &(double){0.0}, DATA(ret), &NROWS(ret));
  
  return LIBBIB_OK;
}

int bib_mmprod_a(const bool transx, const bool transy, cmat_r x, cmat_r y, dmatrix_t **restrict ret)
{
  len_t nrows, ncols;
  
  if (transx)
    nrows = NCOLS(x);
  else
    nrows = NROWS(x);
  
  if (transy)
    ncols = NROWS(y);
  else
    ncols = NCOLS(y);
  
  *ret = newmat(nrows, ncols);
  if (*ret == NULL)
    return LIBBIB_BADMALLOC;
  
  return bib_mmprod(transx, transy, x, y, *ret);
}



// FIXME drop transx/transy args?
int bib_mmadd(const bool transx, const bool transy, cmat_r x, cmat_r y, mat_r ret)
{
  CHECKIFSAME(x, ret);
  CHECKIFSAME(y, ret);
  
  const len_t nrows = NROWS(x);
  const len_t ncols = NCOLS(x);
  
  if (NROWS(y) != nrows || NCOLS(y) != ncols)
    return LIBBIB_INDIMMISMATCH;
  
  for (len_t j=0; j<ncols; j++)
  {
    for (len_t i=0; i<nrows; i++)
    {
      const len_t ind = i + nrows*j;
      DATA(ret)[ind] = DATA(x)[ind] + DATA(y)[ind];
    }
  }
  
  return LIBBIB_OK;
}

int bib_mmadd_a(const bool transx, const bool transy, cmat_r x, cmat_r y, dmatrix_t **restrict ret)
{
  const len_t nrows = NROWS(x);
  const len_t ncols = NCOLS(x);
  
  if (NROWS(y) != nrows || NCOLS(y) != ncols)
    return LIBBIB_INDIMMISMATCH;
  
  *ret = newmat(nrows, ncols);
  if (*ret == NULL)
    return LIBBIB_BADMALLOC;
  
  return bib_mmadd(transx, transy, x, y, *ret);
}
