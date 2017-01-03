CC=gcc
CFLAGS=-std=c99 -O3 -Wall -pedantic -fopenmp
LDFLAGS=../build/libbib.a -llapack -lblas -lm


all: Rpkg

redocument:
	cd Rpkg && redocument

Rpkg: redocument 
	R CMD INSTALL Rpkg


clean:
	cd Rpkg && ./cleanup

