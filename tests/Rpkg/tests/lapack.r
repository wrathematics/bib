library(BIBtests, quietly=TRUE)

CHECK <- function(test, truth) stopifnot(all.equal(test, truth))
TESTING <- function(what) cat(paste0(what, ": "))
OK <- function() cat("ok!\n")


set.seed(1234)
m = 10
n = 5
x = matrix(rnorm(m*n), m, n)
x = cov(x)

cat("# LAPACK\n")


TESTING("invert")
test = bib_invert(x)
truth = solve(x)
CHECK(test, truth)
OK()


cat("\n")
