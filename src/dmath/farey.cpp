#include "farey.hxx"
#include <dmath/utility.hxx>

#include <set>
#include <stdexcept>

#include <dmath/utility.inl>

namespace dmath
{

    std::stack<Pair> create_farey_stack()
    {
        return std::stack<Pair>();
    }

    Pair next_farey(
            Pair const & current,
            std::stack<Pair> & stack,
            size_t const n
    ){
        if (n == 0)
            throw std::runtime_error("Cannot compute Farey sequence of order zero.");
        if (stack.empty())
            throw std::runtime_error("Tried to call next_farey() with empty stack.");

        while (true)
        {
            auto r = stack.top();
            auto const denominator = current.second + r.second;
            if (denominator <= n)
            {
                auto const numerator = current.first + r.first;
                stack.push({numerator, denominator});
            }
            else
            {
                stack.pop();
                return r;
            }
        }
    }

    std::vector<Pair> restricted_farey(
            Pair const & left,
            Pair const & right,
            size_t const n
    ){
        if (left.first * right.second >= left.second * right.first)
            throw std::runtime_error("left must be less than right.");
        if (gcd(left.first, left.second) != 1 || gcd(right.first, right.second) != 1)
            throw std::runtime_error("The given fractions must be reduced (gcd(numerator, denominator) == 1).");

        std::vector<Pair> sequence = {left};
        std::stack<Pair> stack;
        stack.push(right);
        while (!stack.empty())
        {
            sequence.emplace_back(next_farey(sequence.back(), stack, n));
        }
        return sequence;
    }

    std::vector<Pair> farey(
            size_t const n
    ){
        return restricted_farey({0, 1}, {1, 1}, n);
    }

    std::vector<size_t> number_of_summations(
            std::vector<size_t> const & candidates,
            size_t const n
    ){
        std::set<size_t> ordered_candidates(candidates.begin(), candidates.end());
        ordered_candidates.erase(0);

        std::vector<size_t> summations(n+1, 0);
        summations[0] = 1;
        for (auto const c : ordered_candidates)
        {
            if (c > n)
                break;
            for (size_t i = c; i <= n; ++i)
                summations[i] += summations[i-c];
        }
        return summations;
    }

} // namespace dmath
