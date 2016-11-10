library(BIBtests, quietly=TRUE)

CHECK <- function(test, truth) stopifnot(all.equal(test, truth))
TESTING <- function(what) cat(paste0(what, ": "))
OK <- function() cat("ok!\n")


set.seed(1234)
len = 100
x = rnorm(len)
y = rnorm(len)

cat("# Level 1\n")


TESTING("dotprod")
test = bib_dotprod(x, y)
truth = sum(x*y)
CHECK(test, truth)
OK()


TESTING("vnorm")
test = bib_vnorm(x)
truth = sqrt(sum(x*x))
CHECK(test, truth)
OK()


cat("\n")
