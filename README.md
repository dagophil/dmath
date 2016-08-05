# *dmath*

[![Travis CI Status](https://travis-ci.org/dagophil/dmath.svg?branch=master)](https://travis-ci.org/dagophil/dmath)

## What is *dmath*?

*dmath* is a small library for C++ and python that provides some useful math functions.

## Compile

To compile the library, python and cython need to be installed. The test environment uses python 3.5.2 and cython
0.24.1, but older versions (even python 2.7) should work as well.

The library can be compiled by running the following command from the *dmath* directory.
```
python setup.py build_ext --inplace
```
As a result, a library file will be created in the *dmath* directory that can be loaded from python. Depending on your
platform, the filename might be one of the following: `dmath.so`, `dmath.pyd`, `dmath.*.pyd`.

## Usage

Once the library is compiled, it can be loaded from an arbitrary python script by calling `import dmath`. The compiled library file must be copied
to a place where the python script can find it (for example into the same folder as the script).

### Unit tests

To run the unit tests, execute the following command from the *dmath* directory.
```
python -m unittest test
```

### Examples

Check if the given number is prime:
```
>>> import dmath
>>> dmath.is_prime(29)
True
>>> dmath.is_prime(15)
False
```
Compute the prime factors of the given number:
```
>>> import dmath
>>> dmath.prime_factors(7)  # 7 == 7**1
[(7, 1)]
>>> dmath.prime_factors(60)  # 7 == 2**2 + 3**1 + 5**1
[(2, 2), (3, 1), (5, 1)]
```
Compute all prime numbers up to the given number:
```
>>> import dmath
>>> dmath.eratosthenes(30)
[2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
```
Compute the continued fraction of the square root of the given number:
```
>>> import dmath
>>> dmath.cfr(2)  # sqrt(2) == [1; 2] with a period length of 1.
([1, 2], 1)
>>> dmath.cfr(13)  # sqrt(13) == [3; 1, 1, 1, 1, 6] with a period length of 5.
([3, 1, 1, 1, 1, 6], 5)
```
Use the first `n` numbers of the continued fraction to approximate the square root of `d`. Give either `d` itself or
the continued fraction of the square root of `d`:
```
>>> import dmath
>>> dmath.approx_cfr(3, d=2)  # sqrt(2) == [1; 2, 2, 2, ...] => approximation is 1+1/(2+1/(2+1/2)) == 17/12.
(17, 12)
>>> dmath.approx_cfr(3, cfrac=dmath.cfr(2))
(17, 12)
```
