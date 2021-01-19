## 1rep

This binary is compiled by perlcc, which is possible to [uncompile](https://stackoverflow.com/questions/4048614/how-can-i-reverse-engineer-a-perl-program-that-has-been-compiled-with-perlcc) and get perl code.

And the perl code is still too large for manual search, so you shall parse it into a graph and do some pathfinding, any simple algorithm like DFS should work.
