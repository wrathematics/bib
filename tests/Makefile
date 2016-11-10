CC=gcc
CFLAGS=-std=c99 -O3 -Wall -pedantic -fopenmp
LDFLAGS=../libbib.a -llapack -lblas -lm


all: Rpkg

Rpkg: clean
	R CMD INSTALL Rpkg


clean:
	cd Rpkg && ./cleanup

