#ifndef LIBBIB_CDEFS_H__
#define LIBBIB_CDEFS_H__


#define EPSILON 1e-10

#define MAX(a,b) (a<b?b:a)
#define MIN(a,b) (a<b?a:b)

#define LIBBIB_OK                0
#define LIBBIB_BADMALLOC        -1
#define LIBBIB_INDIMMISMATCH   -10
#define LIBBIB_RETDIMMISMATCH  -11
#define LIBBIB_NONSQUARE       -12
#define LIBBIB_RESTRICTFAIL    -13

#define CHECKMALLOC(x) if (x == NULL) return LIBBIB_BADMALLOC
#define CHECKRET(ret)  if (ret != 0)  return ret
#define CHECKIFSAME(x,y) if(x==0) return LIBBIB_RESTRICTFAIL


#endif
