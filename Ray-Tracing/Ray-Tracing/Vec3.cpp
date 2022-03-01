#pragma once
#include <math.h>
#include "Vec3.h"

Vec3::Vec3(const Scalar _x, const Scalar _y, const Scalar _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vec3 Vec3::operator+(const Vec3& v) const
{
	return Vec3(	x + v.x,
					y + v.y, 
					z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const
{
	return Vec3(	x - v.x,
					y - v.y,
					z - v.z);
}

Vec3 Vec3::operator*(const Scalar& num) const
{
	return Vec3(	x * num,
					y * num,
					z * num);
}

Vec3 Vec3::operator/(const Scalar& num) const
{
	return Vec3(	x / num,
					y / num,
					z / num);
}

void Vec3::operator=(const Vec3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vec3::operator+=(const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vec3::operator-=(const Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void Vec3::operator*=(const Scalar& n)
{
	x *= n;
	y *= n;
	z *= n;
}

void Vec3::operator/=(const Scalar& n)
{
	x /= n;
	y /= n;
	z /= n;
}

bool Vec3::operator==(const Vec3& v) const
{
	return (x == v.x &&
			y == v.y &&
			z == v.z);
}

bool Vec3::operator!=(const Vec3& v) const
{
	return (x != v.x &&
			y != v.y &&
			z != v.z);
}

float Vec3::Length() const
{
	return sqrt(pow(x, 2.0f) + pow(y, 2.0f) + +pow(z, 2.0f));
}

void Vec3::Normalize(const Scalar& value)
{
	float vector_length = Length();

	if (vector_length == 0) { return; }

	x = x / vector_length * value;
	y = y / vector_length * value;
	z = z / vector_length * value;
}

Vec3 Vec3::Invert()
{
	x *= -1;
	y *= -1;
	z *= -1;

	return Vec3(x, y, z);
}
