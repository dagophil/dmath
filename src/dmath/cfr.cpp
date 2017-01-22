#include "cfr.hxx"
#include <dmath/utility.hxx>

#include <cmath>
#include <set>
#include <stdexcept>
#include <tuple>

namespace dmath
{
    namespace detail
    {
        /**
         * Computes the next value in the continued fraction of sqrt(d) and update the current variables.
         */
        size_t next_cfr(
                long & b,
                long & c,
                size_t const d
        ){
            auto const x = static_cast<size_t>((c*std::sqrt(d) - b*c) / (d - b*b));
            long const cc = d - b*b;
            long const bb = -b*c - x*cc;

            auto g = gcd(c, gcd(bb, cc));
            if (g < 0)
                g = -g;
            if (cc < 0)
                g = -g;
            b = bb/g;
            c = cc/g;

            return x;
        }
    } // namespace detail

    std::pair<std::vector<size_t>, size_t>
    cfr(
            size_t const d,
            size_t const max_iter
    ){
        using namespace std;

        // The container for the continued fraction.
        vector<size_t> out;

        // Storage for the residuums to recognize periodicity.
        typedef tuple<long, long> tpl;
        set<tpl> s;

        // Initialization.
        long b = static_cast<size_t>(-floor(sqrt(d)));
        long c = 1;
        s.emplace(b, c);
        out.push_back(-b);

        if (static_cast<size_t>(b*b) == d)
            throw runtime_error("cfr(): d must not be a square.");

        // Iteratively compute the values of the continued fraction.
        for (size_t i = 0; i < max_iter; ++i)
        {
            // Compute next value in the continued fraction.
            auto const x = detail::next_cfr(b, c, d);
            out.push_back(x);

            // Check for periodicity.
            auto const p = s.emplace(b, c);
            if (!p.second)
                return make_pair(out, distance(p.first, s.end()));
        }

        return make_pair(out, 0);
    }

    namespace detail
    {
        /**
         * Returns the i-th value of the given continued fraction.
         */
        size_t eval_cfr(
                size_t i,
                std::vector<size_t> const & frac,
                size_t const p
        ){
            if (i < frac.size())
                return frac[i];
            else if (p > 0)
                return frac[i - p * (size_t)std::ceil((double) (i+1-frac.size()) / p)];
            else
                throw std::runtime_error("eval_cfr(): Index out of range for non-periodic continued fraction.");
        } 
    } // namespace detail

    Pair approx_cfr(
            size_t n,
            std::vector<size_t> const & frac,
            size_t const p
    ){
        using namespace std;

        // Initialization.
        size_t a = 1;
        auto b = detail::eval_cfr(n, frac, p);

        // Early out.
        if (n == 0)
            return make_pair(b, 1);

        // Loop over the continued fraction and compute numerator and denominator.
        for (size_t m = n-1; m > 0; --m)
        {
            auto new_b = detail::eval_cfr(m, frac, p)*b+a;
            a = b;
            b = new_b; 
        }
        a += b*detail::eval_cfr(0, frac, p);

        // Divide by the gcd.
        auto d = gcd(a, b);
        return make_pair(a/d, b/d);
    }

} // namespace dmath
