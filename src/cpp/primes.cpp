#include "dmath.hxx"

namespace dmath
{

    bool is_prime(
            size_t const n
    ){
        if (n <= 1)
            return false;
        if (n <= 3)
            return true;
        if (n % 2 == 0 || n % 3 == 0)
            return false;
        for (size_t i = 5; i*i <= n; i+=6)
            if (n % i == 0 || n % (i+2) == 0)
                return false;
        return true;
    }

    std::vector<size_t> eratosthenes(
            size_t const N
    ){
        std::vector<bool> marked(N+1);
        marked[0] = true;
        marked[1] = true;
        for (size_t i = 2; i*i < marked.size(); ++i)
        {
            if (!marked[i])
            {
                for (size_t j = 2; i*j < marked.size(); ++j)
                {
                    marked[i*j] = true;
                }
            }
        }

        std::vector<size_t> primes;
        for (size_t i = 0; i < marked.size(); ++i)
        {
            if (!marked[i])
            {
                primes.push_back(i);
            }
        }

        return primes;
    }

    namespace detail
    {
        /**
         * Finds the largest exponent e such that n is divisible by i^e.
         * n will be divided by i^e. If e > 0 then (i, e) will be appended to factors.
         */
        void div(
                std::vector<Pair> & factors,
                size_t & n,
                size_t const i
        ){
            if (n % i == 0)
            {
                factors.emplace_back(i, 1);
                n /= i;
            }
            while (n % i == 0)
            {
                ++factors.back().second;
                n /= i;
            }
        }
    } // namespace detail

    std::vector<Pair> prime_factors(
            size_t n
    ){
        if (n == 0)
            throw std::runtime_error("Cannot compute prime factors of zero.");

        std::vector<Pair> factors;
        detail::div(factors, n, 2);
        
        for (size_t i = 3; i <= n; i += 2)
        {
            if (i*i > n)
            {
                factors.emplace_back(n, 1);
                break;
            }
            detail::div(factors, n, i);

            if (n == 1)
                break;
        }
        
        if (factors.empty())
            factors.emplace_back(1, 1);
        
        return factors;
    }

    size_t euler_phi(
            size_t n
    ){
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        auto const factors = prime_factors(n);
        for (auto const & p : factors)
        {
            n /= p.first;
            n *= (p.first-1);
        }
        return n;
    }

} // namespace dmath
