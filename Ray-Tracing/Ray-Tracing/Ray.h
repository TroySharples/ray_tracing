#pragma once
#include <stdlib.h>
#include "Vector3.h"

namespace unstd
{
	class Ray
	{
	public:
		Ray(const unstd::Vector3<float>& origin,
			const unstd::Vector3<float>& direction)
			: r_orig(origin), r_dir(direction) {}

		unstd::Vector3<float> r_orig;
		unstd::Vector3<float> r_dir;

		unstd::Vector3<float> origin() const	{ return r_orig; }
		unstd::Vector3<float> direction() const { return r_dir; }
		unstd::Vector3<float> at(float t)		{ return r_orig + t * r_dir; }

		float ray_time;
	};
}