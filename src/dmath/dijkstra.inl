#include "dijkstra.hxx"
#include <dmath/priority_queue.hxx>

#include <set>
#include <stdexcept>

namespace dmath
{

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
