#include <stdio.h>

#include "../cdefs.h"
#include "../types.h"


static int writemat_ascii_csv(FILE *fp, cmat_r x)
{
  const len_t nrows = NROWS(x);
  const len_t ncols = NCOLS(x);
  
  for (len_t i=0; i<nrows; i++)
  {
    for (len_t j=0; j<ncols; j++)
      fprintf(fp, "%23.14e,", DATA(x)[i + nrows*j]);
    
    fprintf(fp, "\n");
  }
  
  return LIBBIB_OK;
}



static int writemat_ascii_arma(FILE *fp, cmat_r x)
{
  const len_t nrows = NROWS(x);
  const len_t ncols = NCOLS(x);
  
  fprintf(fp, "ARMA_MAT_TXT_FN008\n");
  fprintf(fp, "%d %d\n", nrows, ncols);
  
  for (len_t i=0; i<nrows; i++)
  {
    for (len_t j=0; j<ncols; j++)
      fprintf(fp, "%23.14e", DATA(x)[i + nrows*j]);
    
    fprintf(fp, "\n");
  }
  
  return LIBBIB_OK;
}



static int writemat_binary(FILE *fp, cmat_r x)
{
  fwrite(x, sizeof(*x), 1, fp);
  
  return LIBBIB_OK;
}



int bib_mwrite(const char *file, cmat_r x, const int method)
{
  int ret;
  FILE *fp;
  
  fp = fopen(file, "w");
  if (!fp)
    return LIBBIB_WRITE_FAIL;
  
  if (method == LIBBIB_IO_ASCII_CSV)
    ret = writemat_ascii_csv(fp, x);
  else if (method == LIBBIB_IO_ASCII_ARMA)
    ret = writemat_ascii_arma(fp, x);
  else if (method == LIBBIB_IO_BINARY)
    ret = writemat_binary(fp, x);
  else
    ret = LIBBIB_IO_BADMETHOD;
  
  fclose(fp);
  return ret;
}
