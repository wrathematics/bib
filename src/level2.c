#include <stdlib.h>

#include "blas.h"
#include "cdefs.h"
#include "types.h"

// upper triangle of t(x) %*% x
int crossprod(const double alpha, cmat_r x, mat_r cp)
{
  int info = 0;
  if (cp->nrows != x->ncols || cp->ncols != x->ncols)
    return LIBBIB_RETDIMMISMATCH;
  
  dsyrk_(&(char){'l'}, &(char){'t'}, &x->ncols, &x->nrows, &alpha, x->data,
    &x->nrows, &(double){0.0}, cp->data, &x->ncols);
  
  return info;
}



int tcrossprod(const double alpha, cmat_r x, mat_r tcp)
{
  int info = 0;
  if (tcp->nrows != x->nrows || tcp->ncols != x->nrows)
    return LIBBIB_RETDIMMISMATCH;
  
  dsyrk_(&(char){'l'}, &(char){'n'}, &x->nrows, &x->ncols, &alpha, x->data,
    &x->nrows, &(double){0.0}, tcp->data, &x->nrows);
  
  return info;
}
