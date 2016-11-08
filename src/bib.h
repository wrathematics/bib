#ifndef LIBBIB_H_
#define LIBBIB_H_


#include <stdlib.h>

#include "types.h"

// allocators.c
dvector_t *newvec(clen_t len, double *data);
int setvec(clen_t len, double *data, dvector_t *v);

dmatrix_t *newmat(clen_t nrows, clen_t ncols, double *data);
int setmat(clen_t nrows, clen_t ncols, double *data, dmatrix_t *m);


#endif
