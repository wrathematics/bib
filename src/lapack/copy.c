#include "lapack.h"
#include "../cdefs.h"
#include "../bib.h"


int bib_mcopy(cmat_r x, mat_r y)
{
  char uplo = 'a';
  dlacpy_(&uplo, &NROWS(x), &NCOLS(x), DATA(x), &NROWS(x), DATA(y), &NROWS(y));
  
  return LIBBIB_OK;
}

int bib_mcopy_a(cmat_r x, dmatrix_t **restrict y)
{
  *y = newmat(NROWS(x), NCOLS(x));
  if (DATA(*y) == NULL)
    return LIBBIB_BADMALLOC;
  
  return bib_mcopy(x, *y);
}
