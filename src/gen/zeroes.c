#include <string.h>
#include "../bib.h"
#include "../types.h"
#include "../cdefs.h"

int bib_zeroes(dmatrix_t *x)
{
  clen_t nrows = NROWS(x);
  clen_t ncols = NCOLS(x);
  
  double *ptr = DATA(x);
  memset(ptr, 0, nrows*ncols*sizeof(*ptr));
  
  return LIBBIB_OK;
}

int bib_zeroes_a(clen_t nrows, clen_t ncols, dmatrix_t **x)
{
  *x = newmat(nrows, ncols);
  if (*x == NULL)
    return LIBBIB_BADMALLOC;
  
  return bib_zeroes(*x);
}
