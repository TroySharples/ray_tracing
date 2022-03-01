#pragma once
#include "Object.h"
#include "Vector3.h"

namespace unstd
{
	class Sphere : public Object
	{
	public:
		Sphere(float radius_)
			:radius(radius_) {}
		//Hit returns true if a ray intersects with a sphere within the parameters of a given vector3 centre positionand a radius.
		bool hit(const unstd::Vector3<float>&centre, const unstd::Ray r) const override
		{
			unstd::Vector3<float> oc = r.origin() - centre;
			float a = dot(r.direction(), r.direction());
			float b = 2.0 * dot(oc, r.direction());
			float c = dot(oc, oc) - radius * radius;
			float discriminant = (b * b) - (4 * a * c);
			return (discriminant > 0);
		}

	private:
		float radius;
	};
}