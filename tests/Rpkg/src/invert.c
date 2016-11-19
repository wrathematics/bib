#include "RNACI.h"
#include "../../../src/bib.h"


SEXP bib_invert_(SEXP x)
{
  dmatrix_t in, out;
  const int n = nrows(x);
  SEXP ret;
  newRmat(ret, n, n, "dbl");
  
  setmat(n, n, REAL(x), &in);
  setmat(n, n, REAL(ret), &out);
  
  bib_mcopy(&in, &out);
  int check = bib_invert(&out);
  if (check)
    error("check=%d\n", check);
  
  unhideGC();
  return ret;
}
