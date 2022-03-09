#pragma once

#include "Object.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Triangle.h"
#include <vector>
#include <iostream>


namespace unstd
{	
	
	class Polygon
	{
	public:
		Polygon(unstd::Vector3<float>ws_pos)
			: worldspace_position(ws_pos) {}
		Polygon() = default;

		unstd::Vector3<float> get_ws_pos() { return worldspace_position; }
		unstd::Vector3<float> worldspace_position = unstd::Vector3<float>(0.0, 0.0, 0.0);

		std::vector<unstd::Vector3<float>> triangle_vertices;
		std::vector<unstd::Triangle> triangle_list;

		bool checkTrianglesHit(const unstd::Ray& r);
	};

	std::istream& operator>>(std::istream& is, Polygon& p);

}