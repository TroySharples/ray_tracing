#pragma once
#include <iostream>

namespace unstd
{
	template <typename _T = float>
	class Vector2
	{
	public:
		typename _T value_type;
		Vector2() = default;
		Vector2<_T>(_T e0, _T e1)
			: e{ e0, e1 } {}

		_T x() const { return e[0]; }
		_T y() const { return e[1]; }

		_T operator[](int i) const { return e[i]; }
		_T& operator[](int i) { return e[i]; }

		// Vector -> Vector manipulation.
		const Vector2& operator+() const { return *this; }
		Vector2 operator-() const { return Vector2(-e[0], -e[1]); }
		Vector2& operator+=(const Vector2& v2);
		Vector2& operator-=(const Vector2& v2);
		Vector2& operator*=(const Vector2& v2);
		Vector2& operator/=(const Vector2& v2);

		// Scalers.
		Vector2& operator*=(_T t);
		Vector2& operator/=(_T t);

		bool operator ==(const Vector2& other) const
		{
			return (
				other.e[0] == e[0] &&
				other.e[1] == e[1]);
		}

		bool operator !=(const Vector2& other) const
		{
			return (!(*this == other));
		}

		_T length() const
		{
			return sqrt(
				e[0] * e[0] +
				e[1] * e[1]);
		}

		_T squared_length() const
		{
			return
				e[0] * e[0] +
				e[1] * e[1];
		}

		void make_unit_vector();

		_T e[2] = { 0 };
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename _T = float>
	std::istream& operator>>(std::istream& is, Vector2<_T>& t)
	{
		is
			>> t.e[0]
			>> t.e[1];

		return is;
	}

	template <typename _T = float>
	std::ostream& operator<<(std::ostream& os, const Vector2<_T>& t)
	{
		os
			<< (int)t.e[0]
			<< " "
			<< (int)t.e[1];

		return os;
	}

	template <typename _T = float>
	Vector2<_T> operator+(const Vector2<_T>& v1, const Vector2<_T>& v2)
	{
		return Vector2<_T>(
			v1.e[0] + v2.e[0],
			v1.e[1] + v2.e[1]);
	}

	template <typename _T = float>
	Vector2<_T> operator-(const Vector2<_T>& v1, const Vector2<_T>& v2)
	{
		return Vector2<_T>(
			v1.e[0] - v2.e[0],
			v1.e[1] - v2.e[1]);
	}

	template <typename _T = float>
	Vector2<_T> operator*(const Vector2<_T>& v1, const Vector2<_T>& v2)
	{
		return Vector2<_T>(
			v1.e[0] * v2.e[0],
			v1.e[1] * v2.e[1]);
	}

	template <typename _T = float>
	Vector2<_T> operator/(const Vector2<_T>& v1, const Vector2<_T>& v2)
	{
		return Vector2<_T>(
			v1.e[0] / v2.e[0],
			v1.e[1] / v2.e[1]);
	}

	template <typename _T = float>
	Vector2<_T> operator*(_T t, const Vector2<_T>& v)
	{
		return Vector2<_T>(
			v.e[0] * t,
			v.e[1] * t);
	}

	template <typename _T = float>
	Vector2<_T> operator*(const Vector2<_T>& v, _T t)
	{
		return Vector2<_T>(
			v.e[0] * t,
			v.e[1] * t,
			v.e[2] * t);
	}

	template <typename _T = float>
	Vector2<_T> operator/(const Vector2<_T>& v, _T t)
	{
		return Vector2<_T>(
			v.e[0] / t,
			v.e[1] / t);
	}

	template <typename _T = float>
	_T dot(const Vector2<_T>& v1, const Vector2<_T>& v2)
	{
		return
			v1.e[0] * v2.e[0] +
			v1.e[1] * v2.e[1];
	}

	//template <typename _T = float>
	//Vector2<_T> cross(const Vector2<_T>& v1, const Vector2<_T>& v2)
	//{
	//	return Vector2<_T>(
	//		v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
	//		-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
	//		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
	//}

	template <typename _T>
	Vector2<_T>& Vector2<_T>::operator+=(const Vector2<_T>& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];

		return *this;
	}

	template <typename _T>
	Vector2<_T>& Vector2<_T>::operator-=(const Vector2<_T>& v)
	{
		e[0] -= v.e[0];
		e[1] -= v.e[1];

		return *this;
	}

	template <typename _T>
	Vector2<_T>& Vector2<_T>::operator*=(const Vector2<_T>& v)
	{
		e[0] *= v.e[0];
		e[1] *= v.e[1];

		return *this;
	}

	template <typename _T>
	Vector2<_T>& Vector2<_T>::operator/=(const Vector2<_T>& v)
	{
		e[0] /= v.e[0];
		e[1] /= v.e[1];

		return *this;
	}

	template <typename _T>
	Vector2<_T>& Vector2<_T>::operator*=(_T t)
	{
		e[0] *= t;
		e[1] *= t;

		return *this;
	}

	template <typename _T>
	Vector2<_T>& Vector2<_T>::operator/=(_T t)
	{
		_T k = 1.0 / t;

		e[0] *= k;
		e[1] *= k;

		return *this;
	}

	template <typename _T = float>
	Vector2<_T> unit_vector(const Vector2<_T>& v)
	{
		return v / v.length();
	}

	template <typename _T>
	void Vector2<_T>::make_unit_vector()
	{
		_T unit_scaler = 1.0 / length();
		*this *= unit_scaler;
	}


}