#include "RNACI.h"
#include "../../../src/bib.h"


SEXP bib_dotprod_(SEXP x, SEXP y)
{
  dvector_t in1, in2;
  const int len = LENGTH(x);
  SEXP ret;
  newRvec(ret, 1, "dbl");
  
  setvec(len, REAL(x), &in1);
  setvec(len, REAL(y), &in2);
  
  DBL(ret) = dotprod(&in1, &in2);
  
  unhideGC();
  return ret;
}

SEXP bib_vnorm_(SEXP x)
{
  dvector_t in;
  const int len = LENGTH(x);
  SEXP ret;
  newRvec(ret, 1, "dbl");
  
  setvec(len, REAL(x), &in);
  
  DBL(ret) = vnorm(&in);
  
  unhideGC();
  return ret;
}


SEXP bib_vscale_(SEXP alpha, SEXP x)
{
  dvector_t in1, in2;
  const int len = LENGTH(x);
  SEXP ret;
  newRvec(ret, len, "dbl");
  
  setvec(len, REAL(x), &in1);
  setvec(len, REAL(ret), &in2);
  
  vcopy(&in1, &in2);
  vscale(DBL(alpha), &in2);
  
  unhideGC();
  return ret;
}
