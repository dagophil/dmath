#ifndef DMATH_UTILITY_HXX
#define DMATH_UTILITY_HXX

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

namespace dmath
{

    /**
     * Returns true if the given number is a perfect square.
     */
    bool is_square(
            size_t const a
    );

    /**
     * Returns the greatest common divisor of a and b.
     */
    template <typename T>
    T gcd(
            T const a,
            T const b
    );

    /**
     * Returns a vector with indices of the range [begin, end), such that the iteration through [begin, end) in the
     * order of the indices is sorted.
     */
    template <typename ITER, typename COMP>
    std::vector<size_t> index_sort(
            ITER begin,
            ITER end,
            COMP const & comp
    );

    /**
     * Sorts the range [begin, end) using the order of the given index vector.
     * If the index vector was computed by index_sort(), the range [begin, end) will be sorted.
     */
    template <typename ITER>
    void apply_index_sort(
        ITER begin,
        ITER end,
        std::vector<size_t> const & indices
    );

} // namespace dmath

#endif
