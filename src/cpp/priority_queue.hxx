#ifndef DMATH_PRIORITY_QUEUE_HXX
#define DMATH_PRIORITY_QUEUE_HXX

#include "utility.hxx"

namespace dmath
{

    /**
     * A priority queue that always has the element with the lowest score at the top.
     */
    template <typename T, typename SCORER>
    class PriorityQueue
    {
    public:

        typedef SCORER Scorer;
        typedef typename std::result_of<Scorer(T const &)>::type ScoreType;

        /**
         * Initialize the priority queue with the given scorer.
         * The Scorer class must implement operator()(T const & x) which returns the score of item x.
         */
        PriorityQueue(
                Scorer const & scorer
        );

        /**
         * Insert the item into the queue.
         */
        void push(
                T const & item
        );

        /**
         * Remove the top element from the queue.
         */
        void pop();

        /**
         * Return the top element.
         */
        T const & top() const;

        /**
         * Remove the given item from the queue.
         */
        void erase(T const & item);

        /**
         * Resort the given item into the queue.
         * This method should be used if the score of the given item changed after it has been inserted into the queue.
         */
        void reweight(T const & item);

        /**
         * Return true if the queue contains the given item.
         */
        bool contains(
                T const & item
        ) const;

        /**
         * Return the size of the queue.
         */
        size_t size() const;

        /**
         * Return whether the queue is empty.
         */
        bool empty() const;

    private:

        std::vector<T> items;
        std::vector<ScoreType> item_weight;
        Scorer scorer;

    };

    /**
     * Create a priority queue that uses the given scorer.
     * This method can be used to create a priority queue without explicitly naming the SCORER type:
     * auto queue = make_priority_queue<size_t>(scorer);
     */
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

} // namespace dmath

#endif
