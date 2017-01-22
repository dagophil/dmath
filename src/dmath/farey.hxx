#ifndef DMATH_FAREY_HXX
#define DMATH_FAREY_HXX

#include <dmath/datatypes.hxx>

#include <stack>
#include <utility>
#include <vector>

namespace dmath
{

    /**
     * Returns an empty std::stack<Pair>. This is needed for the cython wrappers of next_farey().
     */
    std::stack<Pair> create_farey_stack();

    /**
     * Compute the fraction in the Farey sequence of order n that lies next to the given fraction.
     * If the new fraction is equal to stack.top(), it is removed from the stack.
     * Otherwise, all fractions in the Farey sequence between the new fraction and stack.top() are pushed onto the
     * stack.
     * The whole Farey sequence of order n can be computed by iterating with this function. See farey().
     */
    Pair next_farey(
            Pair const & current,
            std::stack<Pair> & stack,
            size_t const n
    );

    /**
     * Compute the fractions that lie between the given fractions in a Farey sequence of order n.
     * The given fractions must lie next to each other in a Farey sequence of order < n.
     */
    std::vector<Pair> restricted_farey(
            Pair const & left,
            Pair const & right,
            size_t const n
    );

    /**
     * Compute the reduced fractions between 0 and 1 with a denominator less than or equal to n, arranged in order of
     * increasing size. This is also called the Farey sequence of order n.
     */
    std::vector<Pair> farey(
            size_t const n
    );

    /**
     * Returns a vector v where v[x] is the number of possibilities to write x as a sum of the numbers in candidates.
     */
    std::vector<size_t> number_of_summations(
            std::vector<size_t> const & candidates,
            size_t const n
    );

} // namespace dmath

#endif
