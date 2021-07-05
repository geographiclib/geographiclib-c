#  C implementation of the geodesic routines in GeographicLib

The algorithms are documented in

* C. F. F. Karney,
  [Algorithms for geodesics](https://doi.org/10.1007/s00190-012-0578-z),
  J. Geodesy 87, 43-55 (2013);
  [Addenda](https://geographiclib.sourceforge.io/geod-addenda.html).

Here is the documentation on the
[application programming interface](https://geographiclib.sourceforge.io/html/C/)

You can build the library and examples using cmake.  For example, on
Linux systems you might do:
```sh
cmake -B BUILD -S .
make -C BUILD
echo 30 0 29.5 179.5 | BUILD/tools/inverse
```
