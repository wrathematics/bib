#include "blas.h"
#include "types.h"
#include "cdefs.h"

int mmprod(const bool transx, const bool transy, cmat_r x, cmat_r y, mat_r ret)
{
  CHECKIFSAME(x, ret);
  CHECKIFSAME(y, ret);
  
  // m = # rows of op(x)
  // n = # cols of op(y)
  // k = # cols of op(x)
  int im, in, ik;
  char ctransx, ctransy;
  
  
  if (transy)
    ctransy = 'T';
  else
    ctransy = 'N';
  
  if (transx)
  {
    ctransx = 'T';
    
    im = x->ncols;
    ik = x->nrows;
    
    if (transy)
      in = y->nrows;
    else
      in = y->ncols;
  }
  else
  {
    ctransx = 'N';
    
    im = x->nrows;
    ik = x->ncols;
    
    if (transy)
      in = y->nrows;
    else
      in = y->ncols;
  }
  
  // TODO check for conformality
  
  dgemm_(&ctransx, &ctransy, &im, &in, &ik, &(double){1.0}, x->data, &(x->nrows), y->data, &(y->nrows), &(double){0.0}, ret->data, &(ret->nrows));
  
  return LIBBIB_OK;
}



int mmadd(const bool transx, const bool transy, cmat_r x, cmat_r y, mat_r ret)
{
  CHECKIFSAME(x, ret);
  CHECKIFSAME(y, ret);
  
  const len_t nrows = x->nrows;
  const len_t ncols = x->ncols;
  
  if (y->nrows != nrows || y->ncols != ncols)
    return LIBBIB_INDIMMISMATCH;
  
  for (int j=0; j<ncols; j++)
  {
    for (int i=0; i<nrows; i++)
    {
      const len_t ind = i + nrows*j;
      DATA(ret)[ind] = DATA(x)[ind] + DATA(y)[ind];
    }
  }
  
  return LIBBIB_OK;
}
