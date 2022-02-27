#pragma once

class Vector3
{
public:

	typedef float Scalar;

	float x, y, z;

	Vector3(const Scalar x = 0, const Scalar y = 0, const Scalar z = 0);
	~Vector3() = default;

	float getX() { return (int)x; }
	float getY() { return (int)y; }
	float getZ() { return (int)z; }

	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(const Scalar& num) const;
	Vector3 operator/(const Scalar& num) const;

	void operator= (const Vector3& v);
	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(const Scalar& n);
	void operator/=(const Scalar& n);

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;

	float Length() const;
	void Normalize(const Scalar& value = 1.0f);
	Vector3 Invert();
};