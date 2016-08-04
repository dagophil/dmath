# distutils: language=c++

from libcpp.vector cimport vector
from libcpp.pair cimport pair
from libcpp cimport bool

cdef extern from "dmath.hxx" namespace "dmath":
    cdef vector[pair[size_t, size_t]] prime_factors_impl(size_t)
    cdef vector[size_t] eratosthenes_impl(size_t)
    cdef bool is_prime_impl(size_t)
    cdef pair[vector[size_t], size_t] cfr_impl(size_t) except *
    cdef pair[vector[size_t], size_t] cfr_impl(size_t, size_t) except *
    cdef pair[size_t, size_t] approx_cfr_impl(size_t, vector[size_t], size_t)

def prime_factors(size_t n):
    return prime_factors_impl(n)

def eratosthenes(size_t n):
    return eratosthenes_impl(n)
    
def is_prime(size_t n):
    return is_prime_impl(n)

def cfr(size_t d, max_iter=None):
    if max_iter is None:
        return cfr_impl(d)
    else:
        return cfr_impl(d, max_iter)

def approx_cfr(size_t n, d=None, cfrac=None, max_iter=None):
    if d is not None:
        assert cfrac is None
        frac, p = cfr(d, max_iter)
        return approx_cfr_impl(n, frac, p)
    elif cfrac is not None:
        assert d is None
        return approx_cfr_impl(n, cfrac[0], cfrac[1])
    else:
        raise RuntimeError("approx_cfr(): You must pass either d or cfrac.")
