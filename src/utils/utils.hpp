#pragma once

#include "matrix.hpp"

namespace unstd
{
    template <typename _T>
    constexpr _T pow(const _T& a, const _T& b)
    {
            static_assert(std::is_unsigned<_T>::value, "The type must be an unsigned integral");

            _T ret = 1;
            for (size_t i = 0; i < b; i++) ret *= a;
            return ret;
    }

    template <typename _T>
    constexpr _T unsigned_max() 
    {
            return pow<_T>(2, 8 * sizeof(_T)) - 1; 
    }
    
    template <typename _T>
    requires std::floating_point<_T>
    matrix<_T, 3, 3> rotation(_T a, _T b, _T c)
    {
        using namespace std;
        
        // Generates the rotation matrix from the Euler angles
        return { cos(b)*cos(c), sin(a)*sin(b)*cos(c) - cos(a)*sin(c), cos(a)*sin(b)*cos(c) + sin(a)*sin(c),
                 cos(b)*sin(c), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), cos(a)*sin(b)*sin(c) - sin(a)*cos(c),
                 -sin(b),       sin(a)*cos(b),                        cos(a)*cos(b) };
       
    }
}