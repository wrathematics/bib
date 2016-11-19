#include "../bib.h"
#include "../types.h"
#include "../cdefs.h"
#include "safeomp.h"

#define BLOCKSIZE 8 // TODO check cache line explicitly

int bib_xpose(cmat_r x, mat_r tx)
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

int bib_xpose_a(cmat_r x, dmatrix_t **restrict tx)
{
  CHECKIFSAME(x, *tx);
  *tx = newmat(NCOLS(x), NROWS(x));
  if (DATA(*tx) == NULL)
    return LIBBIB_BADMALLOC;
  
  return bib_xpose(x, *tx);
}
