#ifndef DMATH_PRIORITY_QUEUE_HXX
#define DMATH_PRIORITY_QUEUE_HXX

#include "utility.hxx"

namespace dmath
{

    template <typename T, typename SCORER>
    class PriorityQueue
    {
    public:

        typedef SCORER Scorer;
        typedef typename std::result_of<Scorer(T const &)>::type ScoreType;

        PriorityQueue(
                Scorer const & scorer
        );

        void push(
                T const & item
        );

        void pop();

        T const & top() const;

        void reweight();

        bool contains(
                T const & item
        ) const;

        size_t size() const;

        bool empty() const;

    private:

        std::vector<T> items;
        std::vector<ScoreType> item_weight;
        Scorer scorer;

    };

    template <typename T, typename SCORER>
    PriorityQueue<T, SCORER> make_priority_queue(
            SCORER && scorer
    ){
        return PriorityQueue<T, SCORER>(std::forward<SCORER>(scorer));
    }

    ///////////////////////////////////////
    //   PriorityQueue implementations   //
    ///////////////////////////////////////

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
    inline void PriorityQueue<T, SCORER>::reweight()
    {
        auto comp = [this](T const & a, T const & b)
        {
            return this->scorer(a) > this->scorer(b);
        };
        auto const indices = index_sort(this->items.begin(), this->items.end(), comp);
        apply_index_sort(this->items.begin(), this->items.end(), indices);
        apply_index_sort(this->item_weight.begin(), this->item_weight.end(), indices);
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

} // namespace dmath

#endif
