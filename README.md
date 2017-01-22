# *dmath*

[![Travis CI Status](https://travis-ci.org/dagophil/dmath.svg?branch=master)](https://travis-ci.org/dagophil/dmath)

## What is *dmath*?

*dmath* is a small library for C++ and python that provides some useful math functions.

## Compile

To compile the library, python and cython need to be installed. The supported python versions are 2.7 and 3.5, the
supported cython version is 0.24. Other versions might work as well.

The library can be compiled by running the following command from the *dmath* directory.
```
python setup.py build_ext --inplace
```
As a result, a library file will be created in the *dmath* directory that can be loaded from python. Depending on your
platform, the filename might be one of the following: `dmath.so`, `dmath.pyd`, `dmath.*.pyd`.

## Usage

Once the library is compiled, it can be loaded from an arbitrary python script by calling `import dmath`. The compiled
library file must be copied to a place where the python script can find it (for example into the same folder as the
script).

### Unit tests

To run the unit tests, execute the following command from the *dmath* directory.
```
python -m unittest test
```

### Examples

#### is_square(n):
Returns true if `n` is a perfect square, else false.
```
>>> import dmath
>>> dmath.is_square(16)
True
>>> dmath.is_square(15)
False
```

#### is_prime(n):
Returns true if `n` is a prime number, else false.
```
>>> import dmath
>>> dmath.is_prime(29)
True
>>> dmath.is_prime(15)
False
```

#### eratosthenes(n):
Returns a list with all prime numbers up to `n`.
```
>>> import dmath
>>> dmath.eratosthenes(30)
[2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
```

#### prime_factors(n):
Returns the prime factors of `n`.
```
>>> import dmath
>>> dmath.prime_factors(7)  # 7 == 7**1
[(7, 1)]
>>> dmath.prime_factors(60)  # 60 == 2**2 + 3**1 + 5**1
[(2, 2), (3, 1), (5, 1)]
```

#### euler_phi(n):
Returns the value of Euler's totient function of `n`.
```
>>> import dmath
>>> dmath.euler_phi(60)
16
>>> dmath.euler_phi(1139269212)
341877888
```

#### gcd(a, b):
Returns the greates common divisor of `a` and `b`.
```
>>> import dmath
>>> dmath.gcd(12, 18)
6
```

#### cfr(d, max_iter=None):
Returns the continued fraction of the square root of `d`. Uses at most `max_iter` iterations.
```
>>> import dmath
>>> dmath.cfr(2)  # sqrt(2) == [1; 2] with a period length of 1.
([1, 2], 1)
>>> dmath.cfr(13)  # sqrt(13) == [3; 1, 1, 1, 1, 6] with a period length of 5.
([3, 1, 1, 1, 1, 6], 5)
```

#### approx_cfr(n, d=None, cfrac=None, max_iter=None):
Uses the first `n` numbers of the continued fraction of the square root of `d` to approximate the square root of `d`.
Either `d` or `cfrac` must be given and not `None`.

If `cfrac` is given, it must be the continued fraction of the square root of `d`.
If `d` is given, at most `max_iter` iterations are used to compute `cfrac`.
```
>>> import dmath
>>> dmath.approx_cfr(3, d=2)  # sqrt(2) == [1; 2, 2, 2, ...] => approximation is 1+1/(2+1/(2+1/2)) == 17/12.
(17, 12)
>>> dmath.approx_cfr(3, cfrac=dmath.cfr(2))
(17, 12)
```

#### farey(n):
Computes the Farey sequence of order `n`:
```
>>> import dmath
>>> list(dmath.farey(4))
[(0, 1), (1, 4), (1, 3), (1, 2), (2, 3), (3, 4), (1, 1)]
```

The `farey` function returns a generator, so you can iterate through the numbers, even for large input, without using
much memory:
```
>>> import dmath
>>> for x in dmath.farey(4): print(x)
(0, 1)
(1, 4)
(1, 3)
(1, 2)
(2, 3)
(3, 4)
(1, 1)
```

#### restricted_farey(a, b, n):
Computes the Farey sequence of order `n` in the interval `[a, b]`. The numbers `a` and `b` must be reduced fractions
(tuples with 2 elements) in the interval `[0, 1]`.
```
>>> import dmath
>>> list(dmath.restricted_farey((1, 3), (1, 2), 8)):
[(1, 3), (3, 8), (2, 5), (3, 7), (1, 2)]
```

Like `farey`, the `restricted_farey` function returns a generator.

#### number_of_summations(candidates, n):
Returns a list `l` of length `n+1` such that `l[x]` is the number of possibilities to write `x` as a sum of the numbers
in `candidates`.
```
>>> import dmath
>>> dmath.number_of_summations([1, 2, 3], 7)
[1, 1, 2, 3, 4, 5, 7, 8]
```

#### Dijkstra:
The `Dijkstra` class can be used to run Dijkstra's algorithm. As node descriptor, arbitrary positive integers can be
used. The node descriptors are only used to distinguish the nodes. The actual value, or whether the node descriptors are
consecutive or not has no influence on the performance.

##### Dijkstra.\_\_init\_\_(self, edge_weights):
Initializes the class with the given edge weights. The argument `edge_weights` must be a dict, where the key is an edge
and the value is the length of the edge. An edge is a tuple `(a, b)` where `a` and `b` are the names of nodes
(positive integers).

##### Dijkstra.run(source):
Computes the paths from the given node `source` to all other nodes using Dijkstra's algorithm.

##### Dijkstra.path_to(target):
Returns a list with the nodes that lie on the shortest path from `source` to `target`.


##### Dijkstra.distance_to(target):
Returns the distance from `source` to `target`.

##### Dijkstra example:
```
>>> import dmath
>>> edge_weights = {
...     (1, 2): 7,
...     (1, 3): 9,
...     (1, 6): 14,
...     (2, 3): 10,
...     (2, 4): 15,
...     (3, 4): 11,
...     (3, 6): 2,
...     (4, 5): 6,
...     (5, 6): 9
... }
>>> dijkstra = dmath.Dijkstra(edge_weights)
>>> dijkstra.run(1)  # Compute the paths from node 1 to all other nodes.
>>> dijkstra.path_to(5)  # path from node 1 to node 5
[1, 3, 4, 5]
>>> dijkstra.distance_to(5)  # distance from node 1 to node 5
26.0
```
