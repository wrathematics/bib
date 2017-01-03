# libbib

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/bib.png)](https://travis-ci.org/wrathematics/bib)
* **License:** ![License](http://img.shields.io/badge/license-BSD%201--Clause-orange.svg?style=flat)
* **Author:** Drew Schmidt

![logo](logo/logo.png)



BIB is the Basic Interface for the BLAS (and LAPACK), a basic C interface to computational linear algebra.

The BLAS and LAPACK are wonderful libraries, but very difficult to use until you understand their strange syntax and formulation.  Mastering their strange way of thinking can lead to hilariously high-performance code.  But most use-cases don't require their full power.

BIB does away with a lot of these powerful-but-complicated options.  For example, `INCX` arguments for vector operations are always 1, and `LDA` parameters for matrices are always the number of rows of the matrix.  This cost is necessary in order to produce simple, clean interfaces.  If you find this overly restrictive, my opinion is that you should learn to use the BLAS/LAPACK natively.

We also restrict the interface only to dense vectors/matrices.  Single precision matrix algebra makes no sense to me.  (Double) complex may be supported at a later date.

Additionally, BIB has a few optimized utility functions not included in BLAS/LAPACK, such as matrix transpose.



## Building and Installation

To build, you will need:

* A BLAS library
* A LAPACK library
* CMake

To build, just run `make`.

If your BLAS and/or LAPACK libraries are in a strange location, you can build the project doing something like:

```bash
MY_LAPACK_PATH=/path/to/lapack

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_LIBRARY_PATH=${MY_LAPACK_PATH} ..
make
```



## BIB Philosophy and Similar Projects

* [Armadillo](http://arma.sourceforge.net/) is a really great matrix algebra library.  The problem is that it's C++.  If you don't want to bring the C++ linker to the party (especially if you invited Fortran), then this is out.
* There's also [Eigen](http://eigen.tuxfamily.org/), but again, C++.
* [Boost](http://www.boost.org/) probably does something like this, but fuck Boost.
* [PETSc](https://www.mcs.anl.gov/petsc/) is incredible, but it's huge, complicated (and primarily meant for distributed stuff imo), and with C++ linkage (even though it's really a C library at its heart).
* [GSL](https://www.gnu.org/software/gsl/) is an amazing library that has similar matrix stuff (and much more).  One problem is that GSL is HUGE, can be difficult to build from source, and not that commonly installed (e.g. on clusters and supercomputers).  Also it's GPL, which might be distasteful.

There are a million other C++ frameworks I didn't mention, but these are all the big ones, I think.  BIB differs from these projects in that it's:

* Small and easy to build (and hopefully easy to use).
* Pure C, with no C++ linkage.
* Permissively licensed.

I'm actually not aware of another project that meets these criteria.  But even if there is, hopefully you'll find that my approach has a few good ideas in it.



## License

The project is licensed under a very permissive "1-clause" BSD.  The tldr is:

1. I'm not liable for anything and make no warranties or guarantees about the software.
2. You can't strip my copyright notices off of source code.
3. You *do not* have to redistribute the copyright notice on binary distributions of software (but I'm obviously still a copyright holder of BIB, even in binary distributions).

Note that I am not a lawyer and this interpretation could be wrong I guess, though it's my intention.  See the file `LICENSE.md` for the full license terms.  Items 1 and 2 above are non-negotiable, but if you want this dual-licensed under something else for some reason, email me.
