#include <string.h>
#include "../bib.h"
#include "../types.h"
#include "../cdefs.h"

/**
 * @brief Set a the diagonal of a matrix to 1, and 0 elsewhere.
 * 
 * `x` need not be square.
 */
int bib_eye(dmatrix_t *x)
{
  clen_t m = NROWS(x);
  clen_t n = NCOLS(x);
  
  double *ptr = DATA(x);
  memset(ptr, 0, m*n*sizeof(*ptr));
  
  for (lenprod_t i=0; i<m*n; i+=m+1)
    DATA(x)[i] = 1.0;
  
  return LIBBIB_OK;
}

/**
 * @brief Allocate a new matrix whose diagonal elements are 1, and 0 elsewhere.
 * 
 * `nrows` need not equal `ncols`
 */
int bib_eye_a(clen_t nrows, clen_t ncols, dmatrix_t **x)
{
  *x = newmat(nrows, ncols);
  if (*x == NULL)
    return LIBBIB_BADMALLOC;
  
  return bib_eye(*x);
}
