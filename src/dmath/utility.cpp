#include "utility.hxx"

#include <cmath>

namespace dmath
{

    bool is_square(
            size_t const a
    ){
        auto const root = static_cast<size_t>(std::round(std::sqrt(a)));
        return root*root == a;
    }

} // namespace dmath
