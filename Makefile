CC=gcc
CFLAGS=-std=c99 -O3 -Wall -pedantic -fopenmp
LDFLAGS=-llapack -lblas -lm


SRC_BLAS = $(wildcard src/blas/*.c)
SRC_LAPACK = $(wildcard src/lapack/*.c)
SRC_FUNS = $(wildcard src/funs/*.c)
SRC_GEN = $(wildcard src/gen/*.c)
SRC_IO = $(wildcard src/io/*.c)
SRC_MISC = $(wildcard src/misc/*.c)
SRC = $(SRC_BLAS) $(SRC_LAPACK) $(SRC_FUNS) $(SRC_GEN) $(SRC_IO) $(SRC_MISC) $(SRC_MAIN)
OBJ = $(SRC:.c=.o)
LIB = "libbib.a"

all: static

tests: static
	cd tests && make

static: $(OBJ)
	ar rcs $(LIB) $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f $(LIB) $(OBJ)
