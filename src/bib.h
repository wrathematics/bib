#ifndef LIBBIB_H_
#define LIBBIB_H_

#define LIBBIB_VERSION_MAJOR 0
#define LIBBIB_VERSION_MINOR 1
#define LIBBIB_VERSION_PATCH 0


#include <stdlib.h>
#include "types.h"


// ----------------------------------------------------------------------------
// blas/
// ----------------------------------------------------------------------------

// level1.c
double bib_dotprod(cvec_r x, cvec_r y);
double bib_vnorm(cvec_r x);
int bib_vswap(cvec_r x, vec_r y);
int bib_vcopy(cvec_r x, vec_r y);
void bib_vscale(const double alpha, vec_r x);

// level2.c
int bib_crossprod(const double alpha, cmat_r x, mat_r cp);
int bib_crossprod_a(const double alpha, cmat_r x, dmatrix_t **cp);

int bib_tcrossprod(const double alpha, cmat_r x, mat_r tcp);
int bib_tcrossprod_a(const double alpha, cmat_r x, dmatrix_t **tcp);

int bib_mvprod(const bool trans, const double alpha, cmat_r x, cvec_r y, vec_r ret);
int bib_mvprod_a(const bool trans, const double alpha, cmat_r x, cvec_r y, dvector_t **ret);

// level3.c
int bib_mmprod(const bool transx, const bool transy, cmat_r x, cmat_r y, mat_r ret);
int bib_mmprod_a(const bool transx, const bool transy, cmat_r x, cmat_r y, dmatrix_t **restrict ret);

int bib_mmadd(const bool transx, const bool transy, cmat_r x, cmat_r y, mat_r ret);
int bib_mmadd_a(const bool transx, const bool transy, cmat_r x, cmat_r y, dmatrix_t **restrict ret);



// ----------------------------------------------------------------------------
// funs/
// ----------------------------------------------------------------------------

// abs.c
void bib_mabs(mat_r x);

// expm.c
int bib_mexp(const int p, mat_r x, mat_r ret);
int bib_mexp_a(const int p, mat_r x, dmatrix_t **ret);

// minmax.c
double bib_vmin(cvec_r x);
double bib_mmin(cmat_r x);
double bib_vmax(cvec_r x);
double bib_mmax(cmat_r x);

// trace.c
double bib_trace(cmat_r x);



// ----------------------------------------------------------------------------
// gen/
// ----------------------------------------------------------------------------

// eye.c
int bib_eye(dmatrix_t *x);
int bib_eye_a(clen_t nrows, clen_t ncols, dmatrix_t **x);

// zeroes.c
int bib_zeroes(dmatrix_t *x);
int bib_zeroes_a(clen_t nrows, clen_t ncols, dmatrix_t **x);



// ----------------------------------------------------------------------------
// io/
// ----------------------------------------------------------------------------

int bib_mprint(cmat_r x);
int bib_mread(const char *file, dmatrix_t **x, const int method);
int bib_mwrite(const char *file, cmat_r x, const int method);



// ----------------------------------------------------------------------------
// lapack/
// ----------------------------------------------------------------------------

// copy.c
int bib_mcopy(cmat_r x, mat_r y);
int bib_mcopy_a(cmat_r x, dmatrix_t **restrict y);

// lu.c
int bib_invert(mat_r x);

// svd.c
int bib_svd(const svdparam_t *const p, mat_r x, svd_t *restrict svd);
int bib_svd_a(const svdparam_t *const p, mat_r x, svd_t *restrict svd);



// ----------------------------------------------------------------------------
// misc/
// ----------------------------------------------------------------------------

// allocators.c
dvector_t *newvec(clen_t len);
int setvec(clen_t len, double *data, dvector_t *v);

ivector_t *newivec(clen_t len);

dmatrix_t *newmat(clen_t nrows, clen_t ncols);
int setmat(clen_t nrows, clen_t ncols, double *data, dmatrix_t *m);

void freevec(dvector_t *v);
void freeivec(ivector_t *v);
void freemat(dmatrix_t *m);

// diag.c
int bib_diag(cmat_r x, vec_r d);
int bib_diag_a(cmat_r x, dvector_t **d);

// error.c
void bib_errcheck(const int err);

// is_sym.c
bool bib_is_sym(cmat_r x);

// rev.c
void bib_vrev(vec_r x);
void bib_mrev(mat_r x);

// xpose.c
int bib_xpose(cmat_r x, mat_r tx);
int bib_xpose_a(cmat_r x, dmatrix_t **restrict tx);


#endif
