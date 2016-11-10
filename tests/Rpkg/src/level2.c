#include "RNACI.h"
#include "../../../src/bib.h"


SEXP bib_crossprod_(SEXP x)
{
  dmatrix_t in, out;
  const int m = nrows(x);
  const int n = ncols(x);
  SEXP ret;
  newRmat(ret, n, n, "dbl");
  
  setmat(m, n, REAL(x), &in);
  setmat(n, n, REAL(ret), &out);
  
  int check = crossprod(1.0, &in, &out);
  if (check)
    error("check=%d\n", check);
  
  unhideGC();
  return ret;
}

SEXP bib_tcrossprod_(SEXP x)
{
  dmatrix_t in, out;
  const int m = nrows(x);
  const int n = ncols(x);
  SEXP ret;
  newRmat(ret, m, m, "dbl");
  
  setmat(m, n, REAL(x), &in);
  setmat(m, m, REAL(ret), &out);
  
  int check = tcrossprod(1.0, &in, &out);
  if (check)
    error("check=%d\n", check);
  
  unhideGC();
  return ret;
}

SEXP bib_mvprod_(SEXP trans_, SEXP x, SEXP y)
{
  dmatrix_t in1;
  dvector_t in2, out;
  const int m = nrows(x);
  const int n = ncols(x);
  const int trans = INT(trans_);
  SEXP ret;
  const int insize = trans ? m : n;
  const int outsize = trans ? n : m;
  newRvec(ret, outsize, "dbl");
  
  setmat(m, n, REAL(x), &in1);
  setvec(insize, REAL(y), &in2);
  setvec(outsize, REAL(ret), &out);
  
  int check = mvprod(trans, 1.0, &in1, &in2, &out);
  if (check)
    error("check=%d\n", check);
  
  unhideGC();
  return ret;
}
