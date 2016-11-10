#include "RNACI.h"
#include "../../../src/bib.h"


SEXP bib_mmprod_(SEXP x, SEXP y)
{
  dmatrix_t in1, in2, out;
  const int m = nrows(x);
  const int n = ncols(x);
  const int k = ncols(y);
  SEXP ret;
  newRmat(ret, m, k, "dbl");
  
  setmat(m, n, REAL(x), &in1);
  setmat(n, k, REAL(y), &in2);
  setmat(m, k, REAL(ret), &out);
  
  int check = mmprod(false, false, &in1, &in2, &out);
  if (check)
    error("check=%d\n", check);
  
  unhideGC();
  return ret;
}
