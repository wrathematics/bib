#include "../bib.h"
#include "../types.h"
#include "../cdefs.h"
#include "safeomp.h"


int xpose(cmat_r x, mat_r tx)
{
  CHECKIFSAME(x, tx);
  
  const int blocksize = 8; // TODO check cache line explicitly
  const int m = x->nrows;
  const int n = x->ncols;
  const double *const x_data = x->data;
  double *const tx_data = tx->data;
  
  if (m != tx->ncols || n != tx->nrows)
    return LIBBIB_INDIMMISMATCH;
  
  #pragma omp parallel for default(none) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
  for (int j=0; j<n; j+=blocksize)
  {
    for (int i=0; i<m; i+=blocksize)
    {
      for (int col=j; col<j+blocksize && col<n; ++col)
      {
        for (int row=i; row<i+blocksize && row<m; ++row)
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