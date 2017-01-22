#ifndef DMATH_DIJKSTRA_HXX
#define DMATH_DIJKSTRA_HXX

#include <map>
#include <utility>
#include <vector>

namespace dmath
{

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
         * Returns the distance from the source to the target.
         */
        WeightType distance_to(
                NodeType const & target
        ) const;

    private:

        typedef std::vector<std::vector<std::pair<size_t, WeightType> > > InternalEdgeWeights;

        /**
         * Extracts all distinct nodes from the given edge map and writes them into a vector.
         */
        std::vector<NodeType> extract_nodes(
                EdgeWeights const & edge_weights
        ) const;

        /**
         * Creates the mapping {node => index in this->nodes}.
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

} // namespace dmath

#include "dijkstra.inl"

#endif
