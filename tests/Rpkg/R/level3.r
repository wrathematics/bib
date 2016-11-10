#' @export
bib_mmprod = function(x, y)
{
  storage.mode(x) = "double"
  storage.mode(y) = "double"
  .Call("bib_mmprod_", x, y)
}
