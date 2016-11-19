#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../cdefs.h"

void bib_errcheck(const int err)
{
  if (err == LIBBIB_OK)
    return;
  
  fprintf(stderr, "ERROR: ");
  
  if (err == LIBBIB_OK)
    return;
  else if (err == LIBBIB_BADMALLOC)
    fprintf(stderr, "unable to allocate memory (malloc failed)");
  else if (err == LIBBIB_INDIMMISMATCH)
    fprintf(stderr, "input matrices/vectors are not conformable");
  else if (err == LIBBIB_RETDIMMISMATCH)
    fprintf(stderr, "return dimensions impossible for given input(s)");
  else if (err == LIBBIB_NONSQUARE)
    fprintf(stderr, "input matrix is non-square");
  else if (err == LIBBIB_RESTRICTFAIL)
    fprintf(stderr, "inputs must be distinct");
  else if (err == LIBBIB_LAPACKERR)
    fprintf(stderr, "LAPACK error code %d", errno);
  
  // I/O
  else if (err == LIBBIB_IO_BADMETHOD)
    fprintf(stderr, "unknown I/O method");
  else if (err == LIBBIB_READ_FAIL)
    fprintf(stderr, "file read fail");
  else if (err == LIBBIB_WRITE_FAIL)
    fprintf(stderr, "file write fail");
  else if (err == LIBBIB_READ_INVALID)
    fprintf(stderr, "invalid in-file");
  else if (err == LIBBIB_READ_BADVAL)
    fprintf(stderr, "impossible value during file read");
  
  else
    fprintf(stderr, "unknown error code %d; please report this", err);
  
  fprintf(stderr, "\n");
  exit(err);
}
