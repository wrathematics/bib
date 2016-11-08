#include <stdio.h>
#include <stdlib.h>

#include "../cdefs.h"

void bib_errcheck(const int err)
{
  if (err == LIBBIB_OK)
    return;
  
  fprintf(stderr, "ERROR: ");
  
  if (err == LIBBIB_BADMALLOC)
    fprintf(stderr, "unable to allocate memory (malloc failed)");
  else if (err == LIBBIB_INDIMMISMATCH)
    fprintf(stderr, "input matrices/vectors are not conformable");
  else if (err == LIBBIB_RETDIMMISMATCH)
    fprintf(stderr, "return dimensions impossible for given input(s)");
  else if (err == LIBBIB_RESTRICTFAIL)
    fprintf(stderr, "inputs must be distinct");
  else
    fprintf(stderr, "unknown error code %d; please report this", err);
  
  fprintf(stderr, "\n");
  exit(err);
}
