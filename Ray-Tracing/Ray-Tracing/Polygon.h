#pragma once

#include "Object.h"
#include "Vector3.h"

#include <iostream>


namespace unstd
{	
	class Polygon : public Object
	{
		class Triangle
		{
		public:
			typedef unstd::Vector3<float> vertex_t;
			typedef std::array<vertex_t, 3> vertices_t;
			vertices_t vertices;

			Triangle(const vertices_t& vertices_)
				:vertices(vertices_) {};
		};

		bool hit(const unstd::Vector3<float>& centre, const unstd::Ray r) const override
		{
			return true;
		}
	};

	std::istream& operator>>(std::istream& is, Polygon& p);
}