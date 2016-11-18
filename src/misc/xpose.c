#include "../bib.h"
#include "../types.h"
#include "../cdefs.h"
#include "safeomp.h"

#define BLOCKSIZE 8 // TODO check cache line explicitly

int xpose(cmat_r x, mat_r tx)
{
  CHECKIFSAME(x, tx);
  
  const len_t m = x->nrows;
  const len_t n = x->ncols;
  const double *const x_data = x->data;
  double *const tx_data = tx->data;
  
  if (m != tx->ncols || n != tx->nrows)
    return LIBBIB_INDIMMISMATCH;
  
  #pragma omp parallel for default(none) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
  for (len_t j=0; j<n; j+=BLOCKSIZE)
  {
    for (len_t i=0; i<m; i+=BLOCKSIZE)
    {
      for (len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (len_t row=i; row<i+BLOCKSIZE && row<m; ++row)
          tx_data[col + n*row] = x_data[row + m*col];
      }
    }
  }
  
  
  return LIBBIB_OK;
}

int xpose_a(cmat_r x, mat_r tx)
{
  CHECKIFSAME(x, tx);
  int check = setmat(x->ncols, x->nrows, NULL, tx);
  CHECKRET(check);
  
  return xpose(x, tx);
}
