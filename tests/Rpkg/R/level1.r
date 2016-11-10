#' @export
bib_dotprod = function(x, y)
{
  storage.mode(x) = "double"
  storage.mode(y) = "double"
  .Call("bib_dotprod_", x, y)
}
