#ifndef DMATH_PRIMES_HXX
#define DMATH_PRIMES_HXX

#include <dmath/datatypes.hxx>

#include <vector>

namespace dmath
{

    /**
     * Returns true if n is prime, else false.
     */
    bool is_prime(
            size_t const n
    );

    /**
     * Compute the prime numbers in the interval [2, N] and return them.
     */
    std::vector<size_t> eratosthenes(
            size_t const N
    );

    /**
     * Compute the prime factors of n. The output is a vector of pairs (p, e), where p is a prime that divides n and e
     * is the maximum exponent such that p^e divides n.
     * Throws std::runtime_error if input is zero.
     */
    std::vector<Pair> prime_factors(
            size_t n
    );

    /**
     * Compute Euler's totient function for the given number n.
     * Returns the number of positive integers up to n that are relatively prime to n.
     */
    size_t euler_phi(
            size_t n
    );

} // namespace dmath

#endif
