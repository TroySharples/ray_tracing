#pragma once
#include <math.h>
#include "Vec3.h"

Vector3::Vector3(const Scalar _x, const Scalar _y, const Scalar _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(	x + v.x,
					y + v.y, 
					z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(	x - v.x,
					y - v.y,
					z - v.z);
}

Vector3 Vector3::operator*(const Scalar& num) const
{
	return Vector3(	x * num,
					y * num,
					z * num);
}

Vector3 Vector3::operator/(const Scalar& num) const
{
	return Vector3(	x / num,
					y / num,
					z / num);
}

void Vector3::operator=(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void Vector3::operator*=(const Scalar& n)
{
	x *= n;
	y *= n;
	z *= n;
}

void Vector3::operator/=(const Scalar& n)
{
	x /= n;
	y /= n;
	z /= n;
}

bool Vector3::operator==(const Vector3& v) const
{
	return (x == v.x &&
			y == v.y &&
			z == v.z);
}

bool Vector3::operator!=(const Vector3& v) const
{
	return (x != v.x &&
			y != v.y &&
			z != v.z);
}

float Vector3::Length() const
{
	return sqrt(pow(x, 2.0f) + pow(y, 2.0f) + +pow(z, 2.0f));
}

void Vector3::Normalize(const Scalar& value)
{
	float vector_length = Length();

	if (vector_length == 0) { return; }

	x = x / vector_length * value;
	y = y / vector_length * value;
	z = z / vector_length * value;
}

Vector3 Vector3::Invert()
{
	x *= -1;
	y *= -1;
	z *= -1;

	return Vector3(x, y, z);
}
