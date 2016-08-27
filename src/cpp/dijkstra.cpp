#include "dmath.hxx"

#include "priority_queue.hxx"

#include <algorithm>
#include <numeric>

namespace dmath
{

    Dijkstra::Dijkstra(
            EdgeWeights const & edge_weights
    ) :
        nodes(this->extract_nodes(edge_weights)),
        edge_weights(this->extract_weights(edge_weights)),
        source(std::numeric_limits<size_t>::max())
    {}

    void Dijkstra::run(size_t const source)
    {
        this->init(source);

        auto scorer = [this](size_t const node)
        {
            return this->distance.at(node);
        };
        auto queue = make_priority_queue<size_t>(scorer);
        for (auto n : this->nodes)
            queue.push(n);

        while (!queue.empty())
        {
            auto u = queue.top();
            queue.pop();
            for (auto v_pair : this->edge_weights.at(u))
            {
                auto v = v_pair.first;
                auto distance_uv = v_pair.second;
                if (queue.contains(v))
                {
                    auto alternative = this->distance.at(u) + distance_uv;
                    if (alternative < this->distance.at(v))
                    {
                        this->distance[v] = alternative;
                        predecessor[v] = u;
                        queue.reweight(v);
                    }
                }
            }
        }
    }

    std::vector<size_t> Dijkstra::path_to(
            size_t const target
    ) const {
        std::vector<size_t> reversed_path = {target};
        size_t current = target;
        while (current != this->source)
        {
            auto it = this->predecessor.find(current);
            if (it == this->predecessor.end())
                throw std::runtime_error("source and target are not connected.");
            current = it->second;
            reversed_path.push_back(current);
        }
        return std::vector<size_t>(reversed_path.rbegin(), reversed_path.rend());
    }

    std::map<size_t, size_t> const & Dijkstra::get_predecessors() const
    {
        return this->predecessor;
    }

    std::map<size_t, Dijkstra::WeightType> const & Dijkstra::get_distances() const
    {
        return this->distance;
    }

    std::set<size_t> Dijkstra::extract_nodes(EdgeWeights const & edge_weights)
    {
        std::set<size_t> nodes;
        for (auto const & p : edge_weights)
        {
            nodes.insert(p.first.first);
            nodes.insert(p.first.second);
        }
        return nodes;
    }

    Dijkstra::InternalEdgeWeights Dijkstra::extract_weights(EdgeWeights const & edge_weights) const
    {
        InternalEdgeWeights weights;
        for (auto n : this->nodes)
            weights[n];

        for (auto const & p : edge_weights)
        {
            auto edge = p.first;
            auto weight = p.second;
            weights[edge.first][edge.second] = weight;
        }
        return weights;
    }

    void Dijkstra::init(size_t const source)
    {
        this->source = source;
        this->predecessor.clear();
        this->distance.clear();
        for (auto node : this->nodes)
            this->distance[node] = std::numeric_limits<WeightType>::max();
        this->distance[source] = 0;
    }

} // namespace dmath
