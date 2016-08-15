# distutils: language=c++

from libcpp.pair cimport pair
from libcpp.stack cimport stack
from libcpp.vector cimport vector
from libcpp cimport bool


cdef extern from "dmath.hxx":
    cdef bool _cpp_is_prime "dmath::is_prime" (size_t)
    cdef vector[size_t] _cpp_eratosthenes "dmath::eratosthenes" (size_t)
    cdef vector[pair[size_t, size_t]] _cpp_prime_factors "dmath::prime_factors" (size_t) except +
    cdef size_t _cpp_euler_phi "dmath::euler_phi" (size_t)
    cdef size_t _cpp_gcd "dmath::gcd" (size_t, size_t)
    cdef pair[vector[size_t], size_t] _cpp_cfr "dmath::cfr" (size_t) except +
    cdef pair[vector[size_t], size_t] _cpp_cfr "dmath::cfr" (size_t, size_t) except +
    cdef pair[size_t, size_t] _cpp_approx_cfr "dmath::approx_cfr" (size_t, vector[size_t], size_t)
    cdef stack[pair[size_t, size_t]] _cpp_create_farey_stack "dmath::detail::create_farey_stack" ()
    cdef pair[size_t, size_t] _cpp_next_farey "dmath::next_farey" (pair[size_t, size_t], stack[pair[size_t, size_t]], size_t) except +
    cdef vector[size_t] _cpp_number_of_summations "dmath::number_of_summations" (vector[size_t], size_t)


def is_prime(size_t n):
    return _cpp_is_prime(n)


def eratosthenes(size_t n):
    return _cpp_eratosthenes(n)


def prime_factors(size_t n):
    return _cpp_prime_factors(n)


def euler_phi(size_t n):
    return _cpp_euler_phi(n)


def gcd(size_t a, size_t b):
    return _cpp_gcd(a, b)


def cfr(size_t d, max_iter=None):
    if max_iter is None:
        return _cpp_cfr(d)
    else:
        return _cpp_cfr(d, max_iter)


def approx_cfr(size_t n, d=None, cfrac=None, max_iter=None):
    if d is not None:
        assert cfrac is None
        frac, p = cfr(d, max_iter)
        return _cpp_approx_cfr(n, frac, p)
    elif cfrac is not None:
        assert d is None
        return _cpp_approx_cfr(n, cfrac[0], cfrac[1])
    else:
        raise RuntimeError("approx_cfr(): You must pass either d or cfrac.")


def restricted_farey(pair[size_t, size_t] left, pair[size_t, size_t] right, size_t n):
    if n == 0:
        raise RuntimeError("Cannot compute Farey sequence of order zero.")
    if left.first * right.second >= left.second * right.first:
        raise RuntimeError("left must be less than right.")
    if _cpp_gcd(left.first, left.second) != 1 or _cpp_gcd(right.first, right.second) != 1:
        raise RuntimeError("The given fractions must be reduced(gcd(numerator, denominator) == 1).")
    yield left
    s = _cpp_create_farey_stack()
    s.push(right)
    while not s.empty():
        left = _cpp_next_farey(left, s, n)
        yield left


def farey(size_t n):
    return restricted_farey(pair[size_t, size_t]((0, 1)), pair[size_t, size_t]((1, 1)), n)

def number_of_summations(vector[size_t] candidates, size_t n):
    return _cpp_number_of_summations(candidates, n)
