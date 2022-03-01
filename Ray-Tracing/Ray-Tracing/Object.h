#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <array>



namespace unstd
{
	class Object
	{
	public:
		virtual bool hit(const unstd::Vector3<float>& origin, const unstd::Ray r) const = 0;
	};
}