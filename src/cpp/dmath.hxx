#ifndef DMATH_HXX
#define DMATH_HXX

#include <map>
#include <set>
#include <stack>
#include <vector>

namespace dmath
{

    typedef std::pair<size_t, size_t> Pair;

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

    /**
     * Return the greatest common divisor of a and b.
     */
    template <typename T>
    T gcd(
            T const a,
            T const b
    ){
        return b == 0 ? a : gcd(b, a % b);
    }
    // TODO: Move gcd function.

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
     * Return (numerator, denominator) of the n-th approximation fraction of the given continued fraction.
     */
    Pair approx_cfr(
            size_t n,
            std::vector<size_t> const & frac,
            size_t const p
    );

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
     * Counts the number of possibilities to write x as a sum of the numbers in candidates for each x in [0, n].
     */
    std::vector<size_t> number_of_summations(
            std::vector<size_t> const & candidates,
            size_t const n
    );

    /**
     * Implementation of Dijkstra's algoritm.
     */
    class Dijkstra
    {
    public:

        typedef std::pair<size_t, size_t> Edge;
        typedef double WeightType;
        typedef std::map<Edge, WeightType> EdgeWeights;

        /**
         * Initialize Dijkstra's algorithm with the given weights.
         */
        Dijkstra(
                EdgeWeights const & edge_weights
        );

        /**
         * Computes the shortest path from the source node to all other reachable nodes.
         */
        void run(
                size_t const source
        );

        /**
         * Returns predecessors that were computed by run(). If a node has no predecessor (because it is not reachable
         * or because it is the source node), it is not present in the map.
         */
        std::map<size_t, size_t> const & get_predecessors() const;

        /**
         * Returns the distance from the source node to all other nodes.
         */
        std::map<size_t, WeightType> const & get_distances() const;

    private:

        typedef std::map<size_t, std::map<size_t, WeightType> > InternalEdgeWeights;

        /**
         * Returns the set of all nodes that lie on an edge in the given edge_weights.
         */
        std::set<size_t> extract_nodes(
                EdgeWeights const & edge_weights
        );

        /**
         * Transforms the edge weights to the internal format and returns the result.
         */
        InternalEdgeWeights extract_weights(
                EdgeWeights const & edge_weights
        ) const;

        /**
         * Clears the predecessors and sets the distance to 0 for the source node and to infinity for all other nodes.
         */
        void init(
                size_t const source
        );

        std::set<size_t> const nodes;
        InternalEdgeWeights const edge_weights;
        std::map<size_t, WeightType> distance;
        std::map<size_t, size_t> predecessor;
    };

} // namespace dmath

#endif
