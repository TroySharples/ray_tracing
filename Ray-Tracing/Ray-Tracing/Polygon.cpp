// Pollygon.cpp
#include "Polygon.h"
#include "Vector2.h"
#include "Virtex.h"
#include <string>
#include <sstream>
#include <vector>
#include <regex>



std::istream& unstd::operator>>(std::istream& is, Polygon& p)
{
	//std::cout << "Loading polygon info from file..." << std::endl;

	// Vertex
	std::vector<unstd::Vector3<float>> vertex_positions; // v
	std::vector<unstd::Vector2<float>> vertex_texcoords; // vt
	std::vector<unstd::Vector3<float>> vertex_normals;	 // f
	std::vector<unstd::Vector3<float>> vertex_order;
	std::vector<int> test;

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
			for (int i = 0; i < line.size(); i++)
			{
				// If evaluated character is not " ", "/" or "f".
				if (line[i] != 102 &&
					line[i] != 32 &&
					line[i] != 47)
				{
					// If the next character is a number between 0 and 9.
					if ((line[i + 1] % 48) < 9 &&
						line[i + 1] % 48 >= 0)
					{
						int a;
						int b = line[i + 1] % 48;
						if (b == 0 && line[i + 1] != 48)
						{
							a = line[i] % 48;
						}
						else
						{
							// Multiply first number by 10.
							a = line[i] % 48 * 10;
						}						
						test.push_back(a + b);
						//std::cout << a + b << " ";
						i++;
					}
					else
					{
						test.push_back(line[i] % 48);
						//std::cout << line[i] % 48 << " ";
					}
										
				}
			}
		}
		else
		{

		}
		// Debug.
		//std::cout << line << "\n";
	}
	
	//std::cout << "Polygon info loaded." << std::endl;
	

	p.loadPgonInfo(vertex_positions, vertex_texcoords, vertex_normals);
	p.populateTriangles(test);

	return is;
}

//void unstd::Polygon::foo()
//{
//	std::cout << "Foo \n";
//	unstd::Vector3<float> a = unstd::Vector3<float>(-0.5, 0.0, 1.5);
//	unstd::Vector3<float> b = unstd::Vector3<float>(0.5, 0.0, 1.5);
//	unstd::Vector3<float> c = unstd::Vector3<float>(0.0, 0.5, 1.5);
//	std::array<unstd::Vector3<float>, 3> n{ a, b, c };
//	//qbe = unstd::Triangle(n);
//	std::cout << "Loaded\n";
//}

void unstd::Polygon::populateTriangles(std::vector<int>& v)
{
	//std::cout << "Populating triangles into polygon..." << "\n";

	for (int i = 0; i < v.size(); i++)
	{
		if (i == 0 || i % 3 == 0)
		{
			//// Debug.
			//std::cout << vertex_positions[v[i]] << "\n";
			triangle_vertices.push_back(vertex_positions[v[i]]);
		}		
	}

	std::cout << "There are " << triangle_vertices.size() << " vertices." << std::endl;


	// Triangle A loop.
	std::vector<unstd::Vector3<float>> a;
	for (int i = 0; i < triangle_vertices.size();)
	{
		a.push_back(triangle_vertices[i]);
		i += 3;
	}
	std::cout << "A is " << a.size() << "\n";

	// Triangle B loop.
	std::vector<unstd::Vector3<float>> b;
	for (int i = 1; i < triangle_vertices.size();)
	{
		b.push_back(triangle_vertices[i]);
		i += 3;
	}
	std::cout << "B is " << b.size() << "\n";

	// Triangle C loop.
	std::vector<unstd::Vector3<float>> c;
	for (int i = 2; i < triangle_vertices.size();)
	{
		c.push_back(triangle_vertices[i]);
		i += 3;
	}
	std::cout << "C is " << c.size() << "\n";

	/*std::cout << "A is " << a.size() << "\n";
	std::cout << "B is " << b.size() << "\n";
	std::cout << "C is " << c.size() << "\n";*/

	for (int i = 0; i < triangle_vertices.size() / 3; i++)
	{		
		unstd::Vector3<float> x = a[i];
		unstd::Vector3<float> y = b[i];
		unstd::Vector3<float> z = c[i];
		std::array<unstd::Vector3<float>, 3> vertices { x, y, z };
		unstd::Triangle temp_tri(vertices);
		triangle_list.push_back(temp_tri);
	}


	//// Hard coded vertices positions.
	//unstd::Vector3<float> a(0.5, 0.0, 0.0);
	//unstd::Vector3<float> b(-0.5, 0.0, 0.0);
	//unstd::Vector3<float> c(0.0, 0.5, 0.0);
	//std::array<unstd::Vector3<float>, 3> vertices { a, b, c };
	//unstd::Triangle temp_tri(vertices);
	//triangle_list.push_back(temp_tri);
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

void unstd::Polygon::loadPgonInfo(	
	std::vector<unstd::Vector3<float>>& v_pos, 
	std::vector<unstd::Vector2<float>>& v_txcord, 
	std::vector<unstd::Vector3<float>>& v_norm)
{
	//std::cout << "Loading polygon info...\n";
	vertex_positions = v_pos;
	vertex_texcoords = v_txcord;
	vertex_normals = v_norm;
	//std::cout << "Polygon info loaded...\n";
}
