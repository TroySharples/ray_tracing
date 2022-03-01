#include "Objloader.h"


void unstd::Objloader::readFile(const char* file_name)
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
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	unstd::Vector3<float> temp_Vector3;
	unstd::Vector2<float> temp_Vector2;
	int temp_int = 0;

	// File open error.
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	// Read one line at a time.
	while (std::getline(in_file, line))
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
		std::cout << line << "\n";

	}

	// Debug.
	std::cout << "Number of vertices: " << vertex_positions.size() << "\n";

	// Loaded success

}