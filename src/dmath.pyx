# distutils: language=c++

from libcpp.vector cimport vector
from libcpp.pair cimport pair
from libcpp cimport bool

cdef extern from "dmath.hxx":
    cdef bool _cpp_is_prime "dmath::is_prime" (size_t)
    cdef vector[size_t] _cpp_eratosthenes "dmath::eratosthenes" (size_t)
    cdef vector[pair[size_t, size_t]] _cpp_prime_factors "dmath::prime_factors" (size_t) except +
    cdef size_t _cpp_euler_phi "dmath::euler_phi" (size_t)
    cdef pair[vector[size_t], size_t] _cpp_cfr "dmath::cfr" (size_t) except +
    cdef pair[vector[size_t], size_t] _cpp_cfr "dmath::cfr" (size_t, size_t) except +
    cdef pair[size_t, size_t] _cpp_approx_cfr "dmath::approx_cfr" (size_t, vector[size_t], size_t)

def is_prime(size_t n):
    return _cpp_is_prime(n)

def eratosthenes(size_t n):
    return _cpp_eratosthenes(n)

def prime_factors(size_t n):
    return _cpp_prime_factors(n)

def euler_phi(size_t n):
    return _cpp_euler_phi(n)

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
