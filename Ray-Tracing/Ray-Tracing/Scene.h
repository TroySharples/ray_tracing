#pragma once
#include "Polygon.h"
#include "Sphere.h"

namespace unstd
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		void addPgonElement(unstd::Polygon& p);
		void addSphereElement(unstd::Sphere& s);
		unstd::Vector3<float> renderScene(const unstd::Ray& r);



	private:
		std::vector<unstd::Polygon> pgon_list;
		std::vector<unstd::Sphere> sphere_list;


	};
}