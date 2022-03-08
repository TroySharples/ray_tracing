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

		std::vector<unstd::Vector3<float>> vertex_positions; // v
		std::vector<unstd::Vector2<float>> vertex_texcoords; // vt
		std::vector<unstd::Vector3<float>> vertex_normals;	 // vn
		std::vector<int> vertex_order;						 // f

		std::vector<unstd::Vector3<float>> triangle_vertices;
		std::vector<unstd::Triangle> triangle_list;

		void loadPgonInfo(	std::vector<unstd::Vector3<float>>& v_pos,
							std::vector<unstd::Vector2<float>>& v_txcord,
							std::vector<unstd::Vector3<float>>& v_norm);

		void populateTriangles(std::vector<int>& v);
		bool checkTrianglesHit(const unstd::Ray& r);
		/*void foo();*/
	};

	std::istream& operator>>(std::istream& is, Polygon& p);

}