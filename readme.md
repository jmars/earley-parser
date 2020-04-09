# Earley Chart Parser

A c11 implementation of the small and elegant `Earley` chart parsing algorithm.

[Earley Parsing Explained](http://loup-vaillant.fr/tutorials/earley-parsing/)

## Novelties
* Uses [my port of the bartlett garbage collector to c11](https://github.com/jmars/bartlett-gc)
* Earley parsers can handle even left-recursive grammars, something other algorithms go into infinite loops on