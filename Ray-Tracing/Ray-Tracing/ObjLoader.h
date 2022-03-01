#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include "Virtex.h"
#include "Vector2.h"
#include "Vector3.h"
/*
	http://cs.wellesley.edu/~cs307/readings/obj-ojects.html
	http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/#reading-the-file

	Object will load information from a .obj file and store it in 
	std::vectors
*/



namespace unstd
{
	class Objloader
	{
	public:
		Objloader() = default;
		~Objloader() = default;

		//std::vector<unstd::Vector3<float>> vertices;	// v
		//std::vector<unstd::Vector3<float>> uvs;			// vt
		//std::vector<unstd::Vector3<float>> vertices;	// vn

		void readFile(const char* file_name);

	private:

	};

}