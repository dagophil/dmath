#ifndef DMATH_PRIORITY_QUEUE_HXX
#define DMATH_PRIORITY_QUEUE_HXX

#include <type_traits>
#include <vector>

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
     * Creates a priority queue that uses the given scorer.
     * This method can be used to create a priority queue without explicitly naming the SCORER type:
     * auto queue = make_priority_queue<size_t>(scorer);
     */
    template <typename T, typename SCORER>
    PriorityQueue<T, SCORER> make_priority_queue(
            SCORER && scorer
    );

} // namespace dmath

#include "priority_queue.inl"

#endif
