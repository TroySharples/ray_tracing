#pragma once

#include "vector.hpp"

namespace unstd
{
    template <typename _T, size_t _S>
    struct line
    {
        typedef unstd::vector<_T, _S> spacial_t;

        spacial_t operator[](const _T& t) const { return origin + t*direction; }

        spacial_t origin;
        spacial_t direction;
        
        bool orientation = true;
    };
}