#pragma once

#include <cmath>
#include <array>
#include <iostream>
#include <concepts>

namespace unstd 
{
    template <typename _T, size_t _M, size_t _N>
    struct matrix : std::array<_T, _M*_N>
    {
        // Quality-of-life overloads
        bool operator==(const matrix& A) const { return std::equal(this->begin(), this->end(), A.begin()); }
        bool operator!=(const matrix& A) const { return !(*this == A); }
        _T& operator()(size_t m, size_t n) { return (*this)[m*_N + n]; }
        const _T& operator()(size_t m, size_t n) const { return (*this)[m*_N + n]; }

        // Arithmetic overloads
        const matrix& operator+() const { return *this; }
        constexpr matrix operator-() const { return _T(- 1) * matrix<_T, _M, _N>(*this); }
        matrix& operator*=(const _T& t) { for (auto& i : *this) i *= t; return *this; }
        matrix& operator/=(const _T& t) { for (auto& i : *this) i /= t; return *this; }
        matrix& operator+=(const matrix& A) { for (size_t i = 0; i < _M*_N; i++) (*this)[i] += A[i]; return *this; }
        matrix& operator-=(const matrix& A) { return operator+=(-A); }
        matrix& operator*=(const matrix& A) { return *this = *this*A; }
    };

    // Non-member arithmetic overloads
    template <typename _T, size_t _M, size_t _N>
    constexpr matrix<_T, _M, _N> operator+(const matrix<_T, _M, _N>& A, const matrix<_T, _M, _N>& w)
    {
        matrix<_T, _M, _N> ret;
        for (size_t i = 0; i < _M*_N; i++) ret[i] = A[i] + w[i];
        return ret;
    }

    template <typename _T, size_t _M, size_t _N>
    constexpr matrix<_T, _M, _N> operator-(const matrix<_T, _M, _N>& A, const matrix<_T, _M, _N>& w)
    {
        return A + (-w);
    }

    template <typename _T, size_t _M, size_t _N>
    constexpr matrix<_T, _M, _N> operator*(const _T& t, const matrix<_T, _M, _N>& A)
    {
        matrix<_T, _M, _N> ret;
        for (size_t i = 0; i < _M*_N; i++) ret[i] = t*A[i];
        return ret;
    }
    
    template <typename _T, size_t _M, size_t _N, size_t _O>
    constexpr matrix<_T, _M, _O> operator*(const matrix<_T, _M, _N>& A, const matrix<_T, _N, _O>& w)
    {
        matrix<_T, _M, _O> ret = { 0 };
        for (size_t i = 0; i < _M; i++) for (size_t j = 0; j < _N; j++) for (size_t k = 0; k < _O; k++) ret(i, k) += A(i, j)*w(j, k);
        return ret;
    }

    // Ostream overload
    template <typename _T, size_t _M, size_t _N>
    std::ostream& operator<<(std::ostream& os, const matrix<_T, _M, _N>& A)
    {
        if constexpr (std::is_integral<_T>::value)
            for (const auto& i : A) os << (int) i << " ";
        else
            for (const auto& i : A) os << i << " ";

        return os;
    }
}
