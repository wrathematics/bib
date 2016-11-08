# libbib

BIB is the Basic Interface for the BLAS (and LAPACK).

The BLAS and LAPACK are wonderful, but very difficult to use until you understand their strange syntax and formulation.  Mastering this can 

BIB does away with a lot of the powerful but complicated options in BLAS/LAPACK.  For example, `INCX` arguments for vector operations are always 1, and `LDA` parameters for matrices are always the number of rows of the matrix.  This cost is necessary in order to produce simple, clean interfaces.  If you find this overly restrictive, my opinion is that you should learn to use the BLAS/LAPACK natively.



## Building and Installation




## Example Usage




## Similar Projects

* Armadillo is a really great matrix algebra library.  The problem is that it's C++.  If you don't want to bring the C++ linker to the party (especially if you invited Fortran), then this is out.
* There's also Eigen, but again, C++.
* Boost probably does something like this, but fuck Boost.  Also C++.
* PETSc is incredible, but again, huge, and with C++ linkage (even though it's really a C library at its heart).
* GSL is an amazing library that has some matrix stuff.  One problem is that GSL is HUGE, can be difficult to build from source, and not that commonly installed (e.g. on clusters and supercomputers).  Also it's GPL, which might be distasteful.

There are a million other C++ frameworks I didn't mention, but these are all the big ones, I think.  BIB differes in that it's

* Small and easy to build (and hopefully easy to use).
* Pure C.
* Permissively licensed.

I'm actually not aware of another project like this.  But even if there is, hopefully you'll find that my approach has a few good ideas in it.



## License

The project is licensed under a very permissive "1-clause" BSD.  The tldr is:

1. I'm not liable for anything and make no warranties or guarantees about the software.
2. You can't strip my copyright notices off of source code.
3. You *do not* have to redistribute the copyright notice on binary distributions of software.

Note that I am not a lawyer and this interpretation could be wrong I guess, though it's my intention.  See the file `LICENSE.md` for the full license terms.  Items 1 and 2 above are non-negotiable, but if you want this dual-licensed under something else for some reason, email me.
