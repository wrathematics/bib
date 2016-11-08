#ifndef RSVD_TYPES_H
#define RSVD_TYPES_H


#include <stdint.h>
#include <stdbool.h>

typedef int len_t;
typedef const len_t clen_t;

// dense matrix
typedef struct dmatrix_t
{
  len_t nrows;
  len_t ncols;
  double *data;
} dmatrix_t;

typedef struct dvector_t
{
  len_t len;
  double *data;
} dvector_t;

typedef dmatrix_t *const restrict mat_r;
typedef const dmatrix_t *const restrict cmat_r;

typedef dvector_t *const restrict vec_r;
typedef const dvector_t *const restrict cvec_r;



typedef struct svd_t
{
  dvector_t *restrict d;
  dmatrix_t *restrict u;
  dmatrix_t *restrict vt;
  int info;
} svd_t;


#endif
