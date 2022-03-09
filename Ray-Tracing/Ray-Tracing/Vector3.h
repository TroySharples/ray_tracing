#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

/*
	Array based Vector class
	https://noobtuts.com/cpp/fast-vector3-class
*/ 

namespace unstd 
{
	//template size (r,g,b + brightness?)
	template <typename _T = float>
	class Vector3
	{
	public:
		typename _T value_type;
		Vector3() = default;
		// create vector with defined contents
		Vector3<_T>(_T e0, _T e1, _T e2)
			: e{e0, e1, e2} { }

		// get vector values x, y, z, n
		_T x() const { return e[0]; }
		_T y() const { return e[1]; }
		_T z() const { return e[2]; }

		_T operator[](int i) const { return e[i]; }
		_T& operator[](int i) { return e[i]; }

		// vector->vector manipulation
		const Vector3& operator+() const { return *this; }
		Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
		Vector3& operator+=(const Vector3& v2);
		Vector3& operator-=(const Vector3& v2);
		Vector3& operator*=(const Vector3& v2);
		Vector3& operator/=(const Vector3& v2);

		// Scalers.
		Vector3& operator*=(_T t);
		Vector3& operator/=(_T t);

		bool operator ==(const Vector3& other) const 
		{ 
			return (
				other.e[0] == e[0] &&
				other.e[1] == e[1] &&
				other.e[2] == e[2]);
		}

		bool operator !=(const Vector3& other) const
		{
			return (!(*this == other));
		}

		_T length() const
		{
			return sqrt(
				e[0] * e[0] + 
				e[1] * e[1] + 
				e[2] * e[2]);
		}

		_T squared_length() const
		{
			return 
				e[0] * e[0] + 
				e[1] * e[1] + 
				e[2] * e[2];
		}

		void make_unit_vector();

		_T e[3] = { 0 };
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename _T = float>
	std::istream& operator>>(std::istream& is, Vector3<_T>& t)
	{
		is 
			>> t.e[0] 
			>> t.e[1] 
			>> t.e[2];

		return is;
	}

	template <typename _T = float>
	std::ostream& operator<<(std::ostream& os, const Vector3<_T>& t)
	{
		os 
			<< (_T)t.e[0] 
			<< " " 
			<< (_T)t.e[1]
			<< " " 
			<< (_T)t.e[2];

		return os;
	}

	template <typename _T = float>
	Vector3<_T> operator+(const Vector3<_T>& v1, const Vector3<_T>& v2)
	{
		return Vector3<_T>(
			v1.e[0] + v2.e[0], 
			v1.e[1] + v2.e[1], 
			v1.e[2] + v2.e[2]);
	}

	template <typename _T = float>
	Vector3<_T> operator-(const Vector3<_T>& v1, const Vector3<_T>& v2)
	{
		return Vector3<_T>(
			v1.e[0] - v2.e[0], 
			v1.e[1] - v2.e[1], 
			v1.e[2] - v2.e[2]);
	}

	template <typename _T = float>
	Vector3<_T> operator*(const Vector3<_T>& v1, const Vector3<_T>& v2)
	{
		return Vector3<_T>(
			v1.e[0] * v2.e[0], 
			v1.e[1] * v2.e[1], 
			v1.e[2] * v2.e[2]);
	}

	template <typename _T = float>
	Vector3<_T> operator/(const Vector3<_T>& v1, const Vector3<_T>& v2)
	{
		return Vector3<_T>(
			v1.e[0] / v2.e[0], 
			v1.e[1] / v2.e[1], 
			v1.e[2] / v2.e[2]);
	}

	template <typename _T = float>
	Vector3<_T> operator*(_T t, const Vector3<_T>& v)
	{
		return Vector3<_T>(
			v.e[0] * t, 
			v.e[1] * t, 
			v.e[2] * t);
	}

	template <typename _T = float>
	Vector3<_T> operator*(const Vector3<_T>& v, _T t)
	{
		return Vector3<_T>(
			v.e[0] * t, 
			v.e[1] * t, 
			v.e[2] * t);
	}

	template <typename _T = float>
	Vector3<_T> operator/(const Vector3<_T>& v, _T t)
	{
		return Vector3<_T>(
			v.e[0] / t, 
			v.e[1] / t, 
			v.e[2] / t);
	}

	template <typename _T = float>
	_T dot(const Vector3<_T>& v1, const Vector3<_T>& v2)
	{
		return 
			v1.e[0] * v2.e[0] +
			v1.e[1] * v2.e[1] + 
			v1.e[2] * v2.e[2];
	}

	template <typename _T = float>
	Vector3<_T> cross(const Vector3<_T>& v1, const Vector3<_T>& v2)
	{
		return Vector3<_T>(
			v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		  -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
			v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
	}

	template <typename _T>
	Vector3<_T>& Vector3<_T>::operator+=(const Vector3<_T>& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];

		return *this;
	}

	template <typename _T>
	Vector3<_T>& Vector3<_T>::operator-=(const Vector3<_T>& v)
	{
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];

		return *this;
	}

	template <typename _T>
	Vector3<_T>& Vector3<_T>::operator*=(const Vector3<_T>& v)
	{
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];

		return *this;
	}

	template <typename _T>
	Vector3<_T>& Vector3<_T>::operator/=(const Vector3<_T>& v)
	{
		e[0] /= v.e[0];
		e[1] /= v.e[1];
		e[2] /= v.e[2];

		return *this;
	}

	template <typename _T>
	Vector3<_T>& Vector3<_T>::operator*=(_T t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;

		return *this;
	}

	template <typename _T>
	Vector3<_T>& Vector3<_T>::operator/=(_T t)
	{
		_T k = 1.0 / t;

		e[0] *= k;
		e[1] *= k;
		e[2] *= k;

		return *this;
	}

	template <typename _T = float>
	Vector3<_T> unit_vector(const Vector3<_T>& v)
	{
		return v / v.length();
	}

	template <typename _T>
	void Vector3<_T>::make_unit_vector()
	{
		_T unit_scaler = 1.0 / length();
		*this *= unit_scaler;
	}
}