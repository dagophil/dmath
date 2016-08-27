#ifndef DMATH_UTILITY_HXX
#define DMATH_UTILITY_HXX

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

namespace dmath
{

    template <typename ITER, typename COMP>
    std::vector<size_t> index_sort(ITER begin, ITER end, COMP const & comp)
    {
        auto const n = std::distance(begin, end);
        std::vector<size_t> indices(n);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [begin, &comp](size_t const a, size_t const b){
            return comp(*(begin+a), *(begin+b));
        });
        return indices;
    }

    template <typename ITER>
    void apply_index_sort(ITER begin, ITER end, std::vector<size_t> const & indices)
    {
        typedef typename std::iterator_traits<ITER>::value_type ValueType;
        typedef typename std::iterator_traits<ITER>::difference_type DifferenceType;

        auto const n = std::distance(begin, end);
        std::vector<ValueType> v(n);
        for (DifferenceType i = 0; i < n; ++i)
            v[i] = *(begin+indices[i]);
        std::copy(v.begin(), v.end(), begin);
    }

} // namespace dmath

#endif
