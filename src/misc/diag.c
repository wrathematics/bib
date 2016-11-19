#include "../bib.h"
#include "../types.h"
#include "../cdefs.h"


int bib_diag(cmat_r x, vec_r d)
{
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  int pos = 0;
  for (int i=0; i<m*n; i+=n+1)
  {
    DATA(d)[pos] = DATA(x)[i];
    pos++;
  }
  
  return LIBBIB_OK;
}

int bib_diag_a(cmat_r x, dvector_t **d)
{
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const len_t len = MIN(m, n);
  
  *d = newvec(len);
  CHECKMALLOC(*d);
  
  return bib_diag(x, *d);
}
