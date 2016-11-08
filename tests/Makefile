CC=gcc
CFLAGS=-std=c99 -O3 -Wall -pedantic -fopenmp
LDFLAGS=../libbib.a -llapack -lblas -lm


all: clean level2

level2: 
	$(CC) $(CFLAGS) level2.c -o level2 $(LDFLAGS)


clean:
	rm -f level2
