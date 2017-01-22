#include "priority_queue.hxx"

namespace dmath
{

    template <typename T, typename SCORER>
    inline PriorityQueue<T, SCORER>::PriorityQueue(
            Scorer const & scorer
    )   :
        scorer(scorer)
    {}

    template <typename T, typename SCORER>
    inline void PriorityQueue<T, SCORER>::push(
            T const & item
    ){
        auto score = this->scorer(item);
        auto comp = [this](T const & a, double const val)
        {
            return this->scorer(a) > val;
        };
        auto it = std::lower_bound(this->items.begin(), this->items.end(), score, comp);
        auto i = std::distance(this->items.begin(), it);
        this->items.insert(it, item);
        this->item_weight.insert(this->item_weight.begin()+i, score);
    }

    template <typename T, typename SCORER>
    inline void PriorityQueue<T, SCORER>::pop()
    {
        this->items.pop_back();
        this->item_weight.pop_back();
    }

    template <typename T, typename SCORER>
    inline T const & PriorityQueue<T, SCORER>::top() const
    {
        return this->items.back();
    }

    template <typename T, typename SCORER>
    inline void PriorityQueue<T, SCORER>::erase(T const & item)
    {
        auto it = std::find(this->items.begin(), this->items.end(), item);
        if (it != this->items.end())
        {
            auto i = std::distance(this->items.begin(), it);
            this->items.erase(it);
            this->item_weight.erase(this->item_weight.begin()+i);
        }
    }

    template <typename T, typename SCORER>
    inline void PriorityQueue<T, SCORER>::reweight(
            T const & item
    ){
        this->erase(item);
        this->push(item);
    }

    template <typename T, typename SCORER>
    inline bool PriorityQueue<T, SCORER>::contains(
            T const & item
    ) const {
        auto it = std::find(this->items.begin(), this->items.end(), item);
        return it != this->items.end();
    }

    template <typename T, typename SCORER>
    inline size_t PriorityQueue<T, SCORER>::size() const
    {
        return this->items.size();
    }

    template <typename T, typename SCORER>
    inline bool PriorityQueue<T, SCORER>::empty() const
    {
        return this->items.size() == 0;
    }

    template <typename T, typename SCORER>
    PriorityQueue<T, SCORER> make_priority_queue(
            SCORER && scorer
    ){
        return PriorityQueue<T, SCORER>(std::forward<SCORER>(scorer));
    }
    
} // namespace dmath
