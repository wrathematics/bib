#ifndef LIBBIB_H_
#define LIBBIB_H_


#include <stdlib.h>
#include "types.h"


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



// ----------------------------------------------------------------------------
// ./
// ----------------------------------------------------------------------------

// level1.c
double dotprod(cvec_r x, cvec_r y);
double vnorm(cvec_r x);
int vswap(cvec_r x, vec_r y);
int vcopy(cvec_r x, vec_r y);
void vscale(const double alpha, vec_r x);

// level2.c
int crossprod(const double alpha, cmat_r x, mat_r cp);
int crossprod_a(const double alpha, cmat_r x, mat_r cp);

int tcrossprod(const double alpha, cmat_r x, mat_r tcp);
int tcrossprod_a(const double alpha, cmat_r x, mat_r tcp);

int mvprod(const bool trans, const double alpha, cmat_r x, cvec_r y, vec_r ret);
int mvprod_a(const bool trans, const double alpha, cmat_r x, cvec_r y, vec_r ret);

// level3.c
int mmprod(const bool transx, const bool transy, cmat_r x, cmat_r y, mat_r ret);


#endif
