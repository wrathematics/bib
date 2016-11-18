#ifndef LIBBIB_TYPES_H_
#define LIBBIB_TYPES_H_


#include <stdint.h>
#include <stdbool.h>

typedef int32_t len_t;
typedef int64_t lenprod_t; // storage for len_t*len_t
typedef const len_t clen_t;

// dense matrix
typedef struct dmatrix
{
  len_t nrows;
  len_t ncols;
  double *data;
} dmatrix_t;

typedef struct dvector
{
  len_t len;
  double *data;
} dvector_t;

typedef dmatrix_t *const restrict mat_r;
typedef const mat_r cmat_r;

typedef dvector_t *const restrict vec_r;
typedef const vec_r cvec_r;


typedef struct
{
  bool inplace;
  bool retu;
  bool retvt;
  bool descending;
} svdparam_t;

typedef struct
{
  dvector_t *restrict d;
  dmatrix_t *restrict u;
  dmatrix_t *restrict vt;
  int info;
} svd_t;


#endif
