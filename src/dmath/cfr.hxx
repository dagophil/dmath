#ifndef DMATH_CFR_HXX
#define DMATH_CFR_HXX

#include <dmath/datatypes.hxx>

#include <utility>
#include <vector>

namespace dmath
{

    /**
     * Returns a pair (f, p) where f is the continued fraction of sqrt(d) and p is the period length. If p == 0 then
     * the maximum number of iterations was reached before finding the period length.
     * Throws std::runtime_error if d is the square of a natural number.
     */
    std::pair<std::vector<size_t>, size_t>
    cfr(
            size_t const d,
            size_t const max_iter = 2000
    );

    /**
     * Returns (numerator, denominator) of the n-th approximation fraction of the given continued fraction.
     */
    Pair approx_cfr(
            size_t n,
            std::vector<size_t> const & frac,
            size_t const p
    );

} // namespace dmath

#endif
