CC=gcc
CFLAGS=-std=c99 -O3 -Wall -pedantic -fopenmp
LDFLAGS=-llapack -lblas -lm


SRC_MISC = $(wildcard src/misc/*.c)
SRC_MAIN = $(wildcard src/*.c)
SRC = $(SRC_MISC) $(SRC_MAIN)
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

