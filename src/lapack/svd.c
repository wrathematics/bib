#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lapack.h"
#include "../cdefs.h"
#include "../types.h"


int bib_svd(const svdparam_t *const p, mat_r x, svd_t *const restrict svd)
{
  char jobz;
  int info = 0;
  int lwork, *iwork;
  double tmp, *work, *x_cp;
  const int m = x->nrows;
  const int n = x->ncols;
  const bool inplace = p->inplace;
  int minmn = m<n ? m : n;
  
  if (p->retu == 0 && p->retvt == 0)
    jobz = 'n';
  else if ((p->retu == 0 && m >= n) || (p->retvt == 0 && m < n))
    jobz = 'o';
  else if (p->retu <= minmn && p->retvt <= minmn)
    jobz = 's';
  else
    jobz = 'a';
  
  
  if (inplace)
    x_cp = x->data;
  else
  {
    x_cp = malloc(m*n * sizeof(*x_cp));
    memcpy(x_cp, x->data, m*n*sizeof(*x_cp));
    if (x_cp == NULL)
      return LIBBIB_BADMALLOC;
  }
  
  iwork = malloc(8*minmn * sizeof(*iwork));
  if (iwork == NULL)
  {
    if (!inplace)
      free(x_cp);
    return LIBBIB_BADMALLOC;
  }
  
  lwork = -1;
  dgesdd_(&jobz, &m, &n, x_cp, &m, svd->d->data, svd->u->data, &m, svd->vt->data, &minmn, &tmp, &lwork, iwork, &info);
  if (info != 0)
  {
    svd->info = info;
    if (!inplace)
      free(x_cp);
    free(iwork);
    return LIBBIB_LAPACKERR;
  }
  
  lwork = (int) tmp;
  work = malloc(lwork * sizeof(*work));
  if (work == NULL)
  {
    if (!inplace)
      free(x_cp);
    free(iwork);
  }
  
  dgesdd_(&jobz, &m, &n, x_cp, &m, svd->d->data, svd->u->data, &m, svd->vt->data, &minmn, work, &lwork, iwork, &info);
  
  svd->info = info;
  
  if (!inplace)
    free(x_cp);
  free(work);
  free(iwork);
  
  return LIBBIB_OK;
}



int bib_svd_a(const svdparam_t *const p, mat_r x, svd_t *restrict svd)
{
  CHECKIFSAME(x, svd->u);
  CHECKIFSAME(x, svd->vt);
  
  const int m = x->nrows;
  const int n = x->ncols;
  const int minmn = m<n ? m : n;
  
  svd->d->len = minmn;
  svd->d->data = malloc(minmn * sizeof(*svd->d->data));
  if (svd->d->data == NULL)
    goto fail;
  
  if (p->retu)
  {
    svd->u->nrows = n;
    svd->u->ncols = minmn;
    svd->u->data = malloc(svd->u->nrows * svd->u->ncols * sizeof(*svd->u->data));
    if (svd->u->data == NULL)
      goto fail;
  }
  
  if (p->retvt)
  {
    svd->u->nrows = minmn;
    svd->u->ncols = n;
    svd->vt->data = malloc(svd->vt->nrows * svd->vt->ncols * sizeof(*svd->vt->data));
    if (svd->vt->data == NULL)
      goto fail;
  }
  
  
  return bib_svd(p, x, svd);
  
  
fail:
  if (svd->d->data != NULL)
    free(svd->d->data);
  if (svd->u->data != NULL)
    free(svd->u->data);
  if (svd->vt->data != NULL)
    free(svd->vt->data);
  svd = NULL;
  return LIBBIB_BADMALLOC;
}
