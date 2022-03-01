#pragma once

class Vec3
{
public:

	typedef float Scalar;

	float x, y, z;

	Vec3(const Scalar x = 0, const Scalar y = 0, const Scalar z = 0);
	~Vec3() = default;

	float getX() { return (int)x; }
	float getY() { return (int)y; }
	float getZ() { return (int)z; }

	Vec3 operator+(const Vec3& v) const;
	Vec3 operator-(const Vec3& v) const;
	Vec3 operator*(const Scalar& num) const;
	Vec3 operator/(const Scalar& num) const;

	void operator= (const Vec3& v);
	void operator+=(const Vec3& v);
	void operator-=(const Vec3& v);
	void operator*=(const Scalar& n);
	void operator/=(const Scalar& n);

	bool operator==(const Vec3& v) const;
	bool operator!=(const Vec3& v) const;

	float Length() const;
	void Normalize(const Scalar& value = 1.0f);
	Vec3 Invert();
};