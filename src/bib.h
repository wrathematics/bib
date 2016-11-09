#ifndef LIBBIB_H_
#define LIBBIB_H_


#include <stdlib.h>
#include "types.h"


// ----------------------------------------------------------------------------
// lapack/
// ----------------------------------------------------------------------------

// lu.c
int invert(mat_r x, int *info);



// ----------------------------------------------------------------------------
// misc/
// ----------------------------------------------------------------------------

// allocators.c
dvector_t *newvec(clen_t len, double *data);
int setvec(clen_t len, double *data, dvector_t *v);

dmatrix_t *newmat(clen_t nrows, clen_t ncols, double *data);
int setmat(clen_t nrows, clen_t ncols, double *data, dmatrix_t *m);

void freevec(dvector_t *v);
void freemat(dmatrix_t *m);

// error.c
void bib_errcheck(const int err);

// is_sym.c
bool is_sym(cmat_r x);

// rev.c
void reverse_vec(vec_r x);
void reverse_mat(mat_r x);

// xpose.c
int xpose(cmat_r x, mat_r tx);
int xpose_a(cmat_r x, mat_r tx);



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
