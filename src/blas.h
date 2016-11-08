#ifndef LIBBIB_BLAS_H_
#define LIBBIB_BLAS_H_


// misc
void dlassq_(const int *n, double *x, int *incx, double *scale, double *sumsq);



// level 1
void daxpy_(const int *n, const double *a, double *x, int *incx, double *y, int *incy);

void dswap_(const int *n, double *x, int *incx, double *y, const int *incy);

void dcopy_(const int *n, const double *x, const int *incx, double *y, const int *incy);

void dscal_(const int *n, const double *alpha, double *x, const int *incx);



// level 2
void dgemv_(const char *trans, const int *m, const int *n, const double *restrict alpha, 
  const double *restrict a, const int *lda, const double *restrict x, const int *incx, 
  const double *restrict beta, double *restrict y, const int *incy);

void dger_(const int *m, const int *n, const double *restrict alpha, const double *restrict x, 
  const int *incx, const double *restrict y, const int *incy, double *restrict a, 
  const int *lda);

void dsyrk_(const char *uplo, const char *trans, const int *n, const int *k, 
  const double *restrict alpha, const double *restrict a, const int *lda, 
  const double *restrict beta, double *restrict c, const int *ldc);



// level 3
void dgemm_(const char *transa, const char *transb, const int *m, const int *n, 
  const int *k, const double *restrict alpha, const double *restrict a, 
  const int *lda, const double *restrict b, const int *ldb, 
  const double *beta, double *restrict c, const int *ldc);


#endif
