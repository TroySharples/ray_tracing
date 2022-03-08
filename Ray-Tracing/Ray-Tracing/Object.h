#pragma once
#include "Ray.h"
#include <array>



namespace unstd
{
	class Object
	{
	public:
		virtual bool hit(const unstd::Vector3<float>& worldspace_position, const unstd::Ray r) const = 0;
	};
}