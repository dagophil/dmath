#ifndef DMATH_HXX
#define DMATH_HXX

#include <map>
#include <set>
#include <stack>
#include <vector>

#include "priority_queue.hxx"

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
    );

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
    template <typename NODETYPE, typename WEIGHTTYPE>
    class Dijkstra
    {
    public:

        typedef NODETYPE NodeType;
        typedef std::pair<NodeType, NodeType> Edge;
        typedef WEIGHTTYPE WeightType;
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
                NodeType const & source
        );

        /**
         * Returns the shortest path from source to target that was computed by run(). The end points are included.
         * Throws a runtime error if source and target are not connected.
         */
        std::vector<NodeType> path_to(
                NodeType const & target
        ) const;

        /**
         * Return the distance from the source to the target.
         */
        WeightType distance_to(
                NodeType const & target
        ) const;

    private:

        typedef std::vector<std::vector<std::pair<size_t, WeightType> > > InternalEdgeWeights;

        /**
         * Extract all distinct nodes from the given edge map and writes them into a vector.
         */
        std::vector<NodeType> extract_nodes(
                EdgeWeights const & edge_weights
        ) const;

        /**
         * Create the mapping {node => index in this->nodes}.
         */
        std::map<NodeType, size_t> extract_node_indices(
                std::vector<NodeType> const & nodes
        ) const;

        /**
         * Transforms the edge weights to the internal format and returns the result.
         */
        InternalEdgeWeights extract_edge_weights(
                EdgeWeights const & edge_weights,
                std::map<NodeType, size_t> const & node_index
        ) const;

        /**
         * Clears the predecessors and sets the distance to 0 for the source node and to infinity for all other nodes.
         */
        void init(
                NodeType const & source_index
        );

        std::vector<NodeType> const nodes;
        std::map<NodeType, size_t> const node_index;
        InternalEdgeWeights const edge_weights;

        std::vector<WeightType> distance;
        std::vector<size_t> predecessor;
        size_t source_index;
    };

    ///////////////////////////////////////////////////////////
    //   Implementation of templated functions and classes   //
    ///////////////////////////////////////////////////////////

    template <typename T>
    T gcd(
            T const a,
            T const b
    ){
        return b == 0 ? a : gcd(b, a % b);
    }

    template <typename NODETYPE, typename WEIGHTTYPE>
    inline Dijkstra<NODETYPE, WEIGHTTYPE>::Dijkstra(
            EdgeWeights const & edge_weights
    )   :
        nodes(extract_nodes(edge_weights)),
        node_index(extract_node_indices(this->nodes)),
        edge_weights(extract_edge_weights(edge_weights, this->node_index)),
        source_index(std::numeric_limits<size_t>::max())
    {}

    template <typename NODETYPE, typename WEIGHTTYPE>
    inline void
    Dijkstra<NODETYPE, WEIGHTTYPE>::run(
            NodeType const & source
    ){
        this->init(source);

        auto scorer = [this](size_t const i)
        {
            return this->distance[i];
        };
        auto queue = make_priority_queue<size_t>(scorer);
        queue.push(this->source_index);

        std::vector<bool> in_queue(this->nodes.size(), false);
        in_queue[this->source_index] = true;

        std::vector<bool> visited(this->nodes.size(), false);

        while (!queue.empty())
        {
            auto u = queue.top();
            queue.pop();
            visited[u] = true;
            for (auto v_pair : this->edge_weights[u])
            {
                auto v = v_pair.first;
                auto distance_uv = v_pair.second;

                if (!in_queue[v])
                {
                    in_queue[v] = true;
                    queue.push(v);
                }

                if (!visited[v])
                {
                    auto alternative = this->distance[u] + distance_uv;
                    if (alternative < this->distance[v])
                    {
                        this->distance[v] = alternative;
                        predecessor[v] = u;
                        queue.reweight(v);
                    }
                }
            }
        }
    }

    template <typename NODETYPE, typename WEIGHTTYPE>
    inline std::vector<NODETYPE>
    Dijkstra<NODETYPE, WEIGHTTYPE>::path_to(
            NodeType const & target
    ) const {
        std::vector<NodeType> reversed_path = {target};
        size_t current_index = this->node_index.at(target);
        while (current_index != this->source_index)
        {
            auto next = this->predecessor[current_index];
            if (next == std::numeric_limits<size_t>::max())
                throw std::runtime_error("source and target are not connected.");
            reversed_path.push_back(this->nodes[next]);
            current_index = next;
        }
        return std::vector<NodeType>(reversed_path.rbegin(), reversed_path.rend());
    }

    template <typename NODETYPE, typename WEIGHTTYPE>
    inline WEIGHTTYPE
    Dijkstra<NODETYPE, WEIGHTTYPE>::distance_to(
            NodeType const & target
    ) const {
        auto target_index = this->node_index.at(target);
        return this->distance[target_index];
    }

    template <typename NODETYPE, typename WEIGHTTYPE>
    inline std::vector<NODETYPE>
    Dijkstra<NODETYPE, WEIGHTTYPE>::extract_nodes(
            EdgeWeights const & edge_weights
    ) const {
        std::set<NodeType> nodes;
        for (auto const & p : edge_weights)
        {
            nodes.insert(p.first.first);
            nodes.insert(p.first.second);
        }
        return std::vector<NodeType>(nodes.begin(), nodes.end());
    }

    template <typename NODETYPE, typename WEIGHTTYPE>
    inline std::map<NODETYPE, size_t>
    Dijkstra<NODETYPE, WEIGHTTYPE>::extract_node_indices(
            std::vector<NodeType> const & nodes
    ) const {
        std::map<NodeType, size_t> m;
        for (size_t i = 0; i < nodes.size(); ++i)
            m[nodes[i]] = i;
        return m;
    }

    template <typename NODETYPE, typename WEIGHTTYPE>
    typename Dijkstra<NODETYPE, WEIGHTTYPE>::InternalEdgeWeights
    inline Dijkstra<NODETYPE, WEIGHTTYPE>::extract_edge_weights(
            EdgeWeights const & edge_weights,
            std::map<NodeType, size_t> const & node_index
    ) const {
        InternalEdgeWeights weights(node_index.size());
        for (auto const & p : edge_weights)
        {
            auto u = node_index.at(p.first.first);
            auto v = node_index.at(p.first.second);
            auto weight = p.second;
            weights[u].emplace_back(v, weight);
        }
        return weights;
    }

    template <typename NODETYPE, typename WEIGHTTYPE>
    inline void
    Dijkstra<NODETYPE, WEIGHTTYPE>::init(
            NodeType const & source
    ){
        this->source_index = this->node_index.at(source);
        this->distance.resize(this->nodes.size());
        std::fill(this->distance.begin(), this->distance.end(), std::numeric_limits<WeightType>::max());
        this->distance[this->source_index] = 0;
        this->predecessor.resize(this->nodes.size());
        std::fill(this->predecessor.begin(), this->predecessor.end(), std::numeric_limits<size_t>::max());
    }

} // namespace dmath

#endif
