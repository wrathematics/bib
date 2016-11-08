#include "blas.h"
#include "types.h"


void mmprod(const bool transx, const bool transy, cmat_r x, cmat_r y, mat_r ret)
{
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
  
  dgemm_(&ctransx, &ctransy, &im, &in, &ik, &(double){1.0}, x->data, &(x->nrows), y->data, &(y->nrows), &(double){0.0}, ret->data, &(ret->nrows));
}
