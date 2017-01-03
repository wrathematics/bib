#include <stdio.h>

#include "../bib.h"
#include "../cdefs.h"


int bib_version()
{
  printf("libbib version: %d.%d-%d\n", LIBBIB_VERSION_MAJOR, LIBBIB_VERSION_MINOR, LIBBIB_VERSION_PATCH);
  
  return LIBBIB_OK;
}
