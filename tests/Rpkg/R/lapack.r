#' @export
bib_invert = function(x)
{
  storage.mode(x) = "double"
  .Call("bib_invert_", x)
}
