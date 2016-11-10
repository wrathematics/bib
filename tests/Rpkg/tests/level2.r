library(BIBtests, quietly=TRUE)

CHECK <- function(test, truth) stopifnot(all.equal(test, truth))
TESTING <- function(what) cat(paste0(what, ": "))
OK <- function() cat("ok!\n")


set.seed(1234)
m = 10
n = 3
x = matrix(rnorm(m*n), m, n)

cat("# Level 2")


TESTING("crossprod")
test = bib_crossprod(x)
truth = crossprod(x)
CHECK(test, truth)
OK()


TESTING("tcrossprod")
test = bib_tcrossprod(x)
truth = tcrossprod(x)
CHECK(test, truth)
OK()


TESTING("mvprod")
y = 1:n
test = bib_mvprod(FALSE, x, y)
truth = x %*% y
dim(truth) <- NULL
CHECK(test, truth)

y = 1:m
test = bib_mvprod(TRUE, x, y)
truth = t(x) %*% y
dim(truth) <- NULL
CHECK(test, truth)
OK()


cat("\n")
