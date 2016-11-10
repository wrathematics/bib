#' @export
bib_dotprod = function(x, y)
{
  storage.mode(x) = "double"
  storage.mode(y) = "double"
  .Call("bib_dotprod_", x, y)
}

#' @export
bib_vnorm = function(x)
{
  storage.mode(x) = "double"
  .Call("bib_vnorm_", x)
}

#' @export
bib_vscale = function(alpha, x)
{
  storage.mode(x) = "double"
  .Call("bib_vscale_", as.double(alpha), x)
}
