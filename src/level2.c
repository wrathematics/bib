#include <stdlib.h>

#include "bib.h"
#include "blas.h"
#include "cdefs.h"

#define BLOCKSIZE 8 // TODO check cache line explicitly

// Copy lower triangle to upper
static inline void symmetrize(const len_t n, double *restrict x)
{
  // #pragma omp parallel for default(none) shared(x) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
  for (len_t j=0; j<n; j+=BLOCKSIZE)
  {
    for (len_t i=j+1; i<n; i+=BLOCKSIZE)
    {
      for (len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (len_t row=i; row<i+BLOCKSIZE && row<n; ++row)
          x[col + n*row] = x[row + n*col];
      }
    }
  }
}

// upper triangle of t(x) %*% x
int crossprod(const double alpha, cmat_r x, mat_r cp)
{
  CHECKIFSAME(x, cp);
  int info = 0;
  if (cp->nrows != x->ncols || cp->ncols != x->ncols)
    return LIBBIB_RETDIMMISMATCH;
  
  dsyrk_(&(char){'l'}, &(char){'t'}, &x->ncols, &x->nrows, &alpha, x->data,
    &x->nrows, &(double){0.0}, cp->data, &x->ncols);
  
  symmetrize(cp->nrows, cp->data);
  
  return info;
}

int crossprod_a(const double alpha, cmat_r x, mat_r cp)
{
  CHECKIFSAME(x, cp);
  int check = setmat(x->ncols, x->ncols, NULL, cp);
  CHECKRET(check);
  
  return crossprod(alpha, x, cp);
}

int tcrossprod(const double alpha, cmat_r x, mat_r tcp)
{
  CHECKIFSAME(x, tcp);
  int info = 0;
  if (tcp->nrows != x->nrows || tcp->ncols != x->nrows)
    return LIBBIB_RETDIMMISMATCH;
  
  dsyrk_(&(char){'l'}, &(char){'n'}, &x->nrows, &x->ncols, &alpha, x->data,
    &x->nrows, &(double){0.0}, tcp->data, &x->nrows);
    
  symmetrize(tcp->nrows, tcp->data);
  
  return info;
}

int tcrossprod_a(const double alpha, cmat_r x, mat_r tcp)
{
  CHECKIFSAME(x, tcp);
  int check = setmat(x->nrows, x->nrows, NULL, tcp);
  CHECKRET(check);
  
  return crossprod(alpha, x, tcp);
}



// ret = alpha*x*y
int mvprod(const bool trans, const double alpha, cmat_r x, cvec_r y, vec_r ret)
{
  CHECKIFSAME(y, ret);
  char t;
  if (trans)
  {
    if (y->len != x->nrows)
      return LIBBIB_INDIMMISMATCH;
    else if (ret->len != x->ncols)
      return LIBBIB_RETDIMMISMATCH;
    
    t = 'T';
  }
  else
  {
    if (y->len != x->ncols)
      return LIBBIB_INDIMMISMATCH;
    else if (ret->len != x->nrows)
      return LIBBIB_RETDIMMISMATCH;
    
    t = 'N';
  }
  
  dgemv_(&t, &x->nrows, &x->ncols, &alpha, x->data, &x->nrows, y->data, &(int){1}, &(double){0.0}, ret->data, &(int){1});
  return LIBBIB_OK;
}

int mvprod_a(const bool trans, const double alpha, cmat_r x, cvec_r y, vec_r ret)
{
  CHECKIFSAME(y, ret);
  len_t len;
  if (trans)
    len = x->ncols;
  else
    len = x->nrows;
  
  int check = setvec(len, NULL, ret);
  CHECKRET(check);
  
  return mvprod(trans, alpha, x, y, ret);
}
