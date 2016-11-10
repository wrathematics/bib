library(BIBtests, quietly=TRUE)

CHECK <- function(test, truth) stopifnot(all.equal(test, truth))
TESTING <- function(what) cat(paste0(what, ": "))
OK <- function() cat("ok!\n")


set.seed(1234)
m = 10
n = 3
k = 4
x = matrix(rnorm(m*n), m, n)
y = matrix(rnorm(n*k), n, k)

cat("# Level 3\n")


TESTING("mmprod")
test = bib_mmprod(x, y)
truth = x %*% y
CHECK(test, truth)
OK()


cat("\n")
