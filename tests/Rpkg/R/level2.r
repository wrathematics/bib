#' @export
bib_crossprod = function(x)
{
  storage.mode(x) = "double"
  .Call("bib_crossprod_", x)
}

#' @export
bib_tcrossprod = function(x)
{
  storage.mode(x) = "double"
  .Call("bib_tcrossprod_", x)
}

#' @export
bib_mvprod = function(trans=FALSE, x, y)
{
  storage.mode(x) = "double"
  storage.mode(y) = "double"
  .Call("bib_mvprod_", trans, x, y)
}
