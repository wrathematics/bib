#include <stdio.h>

#include "../cdefs.h"
#include "../types.h"


int bib_mprint(cmat_r x)
{
  const len_t nrows = NROWS(x);
  const len_t ncols = NCOLS(x);
  
  for (len_t i=0; i<nrows; i++)
  {
    for (len_t j=0; j<ncols; j++)
      printf("%23.14e", DATA(x)[i + nrows*j]);
    
    printf("\n");
  }
  
  return LIBBIB_OK;
}
