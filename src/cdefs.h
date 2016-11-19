#ifndef LIBBIB_CDEFS_H_
#define LIBBIB_CDEFS_H_


#define EPSILON 1e-10

#define MAX(a,b) (a<b?b:a)
#define MIN(a,b) (a<b?a:b)

#define LENGTH(x) ((x)->len)
#define NROWS(x) ((x)->nrows)
#define NCOLS(x) ((x)->ncols)
#define DATA(x) ((x)->data)

#define CHECKMALLOC(x) if (x == NULL) return LIBBIB_BADMALLOC
#define CHECKRET(ret)  if (ret != 0)  return ret
#define CHECKIFSAME(x,y) if (x==y) return LIBBIB_RESTRICTFAIL


// -------------------------------------------------------------
// Error codes
// -------------------------------------------------------------
#define LIBBIB_OK                0
#define LIBBIB_BADMALLOC        -1

#define LIBBIB_INDIMMISMATCH   -10
#define LIBBIB_RETDIMMISMATCH  -11
#define LIBBIB_NONSQUARE       -12
#define LIBBIB_RESTRICTFAIL    -13

#define LIBBIB_LAPACKERR       -101

// I/O
#define LIBBIB_IO_ASCII_CSV  0
#define LIBBIB_IO_ASCII_ARMA 1
#define LIBBIB_IO_BINARY     2

#define LIBBIB_IO_BADMETHOD -1001
#define LIBBIB_READ_FAIL    -1002
#define LIBBIB_WRITE_FAIL   -1003

#define LIBBIB_READ_INVALID -1010
#define LIBBIB_READ_BADVAL  -1011


#endif
