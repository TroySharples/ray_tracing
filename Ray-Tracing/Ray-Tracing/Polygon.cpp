// Pollygon.cpp
#include "Polygon.h"
#include "Vector2.h"
#include "Virtex.h"
#include <sstream>
#include <vector>



std::istream& unstd::operator>>(std::istream& is, Polygon& p)
{
	// Vertex
	std::vector<unstd::Vector3<float>> vertex_positions; // v
	std::vector<unstd::Vector2<float>> vertex_texcoords; // vt
	std::vector<unstd::Vector3<float>> vertex_normals;	 // f

	// Face vectors
	std::vector<int> vertex_position_indicies;
	std::vector<int> vertex_texcoord_indicies;
	std::vector<int> vertex_normal_indicies;

	// Vertex array
	std::vector<unstd::Virtex> vertices;

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	unstd::Vector3<float> temp_Vector3;
	unstd::Vector2<float> temp_Vector2;
	int temp_int = 0;	

	// Read one line at a time.
	while (std::getline(is, line))
	{
		// Get the prefix of the line.
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "s")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else if (prefix == "v")
		{
			ss >> temp_Vector3[0] >> temp_Vector3[1] >> temp_Vector3[2];
			vertex_positions.push_back(temp_Vector3);
		}
		else if (prefix == "vt")
		{
			ss >> temp_Vector2[0] >> temp_Vector2[1];
			vertex_texcoords.push_back(temp_Vector2);
		}
		else if (prefix == "vn")
		{
			ss >> temp_Vector3[0] >> temp_Vector3[1] >> temp_Vector3[2];
			vertex_normals.push_back(temp_Vector3);
		}
		else if (prefix == "f")
		{

		}
		else
		{

		}

		// Debug.
		//std::cout << line << "\n";

	}

	//p.loadPgonInfo(vertex_positions, vertex_texcoords, vertex_normals);

	return is;
}

//void unstd::Polygon::loadPgonInfo(	
//	std::vector<unstd::Vector3<float>>& v_pos, 
//	std::vector<unstd::Vector2<float>>& v_txcord, 
//	std::vector<unstd::Vector3<float>>& v_norm)
//{
//	std::cout << "Loading polygon info...\n";
//	vertex_positions = v_pos;
//	vertex_texcoords = v_txcord;
//	vertex_normals = v_norm;
//
//	//foo();
//}