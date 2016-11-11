#ifndef LIBBIB_LAPACK_H_
#define LIBBIB_LAPACK_H_


// auxiliary routines
void dlacpy_(const char *uplo, const int *m, const int *n, const double *a,
  const int *lda, double *b, const int *ldb);

// the rest
void dlassq_(int *n, double *x, int *incx, double *scale, double *sumsq);

void dgeqrf_(const int *m, const int *n, double *restrict a, const int *lda, 
  double *restrict tau, double *restrict work, const int *restrict lwork, 
  int *info);

void dorgqr_(const int *m, const int *n, const int *k, double *restrict a, 
  const int *lda, double *restrict tau, double *restrict work, const int *lwork, int *info);


void dgetrf_(const int *m, const int *n, double *restrict a, const int *lda, int *ipiv, int *info);

void dgetri_(const int *n, double *restrict a, const int *lda, int *ipiv, double *restrict work, int *lwork, int *info);

void dgesdd_(const char *jobz, const int *m, const int *n, double *a, 
  const int *lda, double *restrict s, double *restrict u, const int *restrict ldu, double *restrict vt, 
  const int *ldvt, double *restrict work, const int *lwork, int *iwork, int *info);

void dsyevd_(const char *jobz, const char *uplo, const int *n, double *restrict a, 
  const int *lda, double *restrict w, double *restrict work, const int *lwork, int *restrict iwork, 
  const int *liwork, int *info);

void dsyevr_(char *jobz, char *range, char *uplo, int *n, double *a, int *lda, double *vl, double *vu, int *il, int *iu, double *abstol, int *m, double *w, double *z, int *ldz, int *isuppz, double *work, int *lwork, int *iwork, int *liwork, int *info);

void dgeev_(char *jobvl, char *jobvr, int *n, double *a, int *lda, double *wr, double *wi, double *vl, int *ldvl, double *vr, int *ldvr, double *work, int *lwork, int *info);


#endif
