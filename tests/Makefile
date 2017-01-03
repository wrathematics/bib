CC=gcc
CFLAGS=-std=c99 -O3 -Wall -pedantic -fopenmp
LDFLAGS=../build/libbib_static.a -llapack -lblas -lm


all: Rpkg level2

level2:
	$(CC) $(CFLAGS) level2.c -o level2 $(LDFLAGS)

redocument:
	cd Rpkg && redocument

Rpkg: redocument 
	R CMD INSTALL Rpkg


cleanup:
	cd Rpkg && ./cleanup

clean: cleanup
	rm -f level2
