#pragma once

#include "Ray.h"
#include "Object.h"
//#include "Colour.h"
#include <array>

namespace unstd
{
	class Triangle : Object
	{
	public:
		typedef unstd::Vector3<float> vertex_t;
		typedef std::array<vertex_t, 3> vertices_t;
		vertices_t vertices;
		Triangle() = default;		
		Triangle(const vertices_t& vertices_)
			:vertices(vertices_) {};
		
		//unstd::Colour c = unstd::Colour(unstd::Vector3<float>(1, 0, 0));
		const float kEpsilon = 1e-8;
		bool hit(const unstd::Vector3<float>& worldspace_position, const unstd::Ray r) const override;

		unstd::Vector3<float> a() const { return vertices[0]; }
		unstd::Vector3<float> b() const { return vertices[1]; }
		unstd::Vector3<float> c() const { return vertices[2]; }
	};
}