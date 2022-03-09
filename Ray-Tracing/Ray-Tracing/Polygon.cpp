// Polygon.cpp
#include "Polygon.h"
#include "Vector2.h"
#include "Virtex.h"
#include <string>
#include <sstream>
#include <vector>
#include <regex>



std::istream& unstd::operator>>(std::istream& is, Polygon& p)
{
	std::cout << "Loading polygon info from file..." << std::endl;

	std::vector<unstd::Vector3<float>> vertexes;
	std::vector<std::array<size_t, 3>> mesh;


	// Read until the end of the file
	while (is)
	{
		// Get the prefix of the line.
		std::string prefix;
		is >> prefix;

		if (prefix == "v")
		{
			// Read the vertex positions
			vertexes.emplace_back();
			unstd::Vector3<float>& vertex = vertexes.back();

			is >> vertex[0] >> vertex[1] >> vertex[2];
		}
		else if (prefix == "f")
		{
			// Read the mesh (how all the vertexes are joined together to create triangles
			mesh.emplace_back();
			std::array<size_t, 3>& net = mesh.back();

			// We only care about the first coordinate for now
			for (auto& i : net)
				is >> i;
		}

		// Read until the end of the line
		is.ignore(64, '\n');
	}

	// Create the triangle vector out of these
	p.triangle_list.clear();
	for (const auto& net : mesh)
	{
		p.triangle_list.emplace_back();
		auto& triangle = p.triangle_list.back();

		for (size_t j = 0; j < net.size(); j++)
		{
			triangle.vertices[j] = vertexes[net[j] - 1];
		}
	}

	return is;
}

bool unstd::Polygon::checkTrianglesHit(const unstd::Ray& r)
{
	for (int i = 0; i < triangle_list.size(); i++)
	{
		if (triangle_list[i].hit(worldspace_position, r))
		{
			return true;
		}
	}
	return false;
}