#include "Scene.h"
#include "Colour.h"

void unstd::Scene::addPgonElement(unstd::Polygon& p)
{
	pgon_list.push_back(p);
}

void unstd::Scene::addSphereElement(unstd::Sphere& s)
{
	sphere_list.push_back(s);
}

unstd::Vector3<float> unstd::Scene::renderScene(const unstd::Ray& r)
{
	const unstd::Vector3<float> background_colour_a = unstd::Vector3<float>(1.0, 1.0, 1.0);
	const unstd::Vector3<float> background_colour_b = unstd::Vector3<float>(0.0, 0.0, 0.0);

	for (int i = 0; i < pgon_list.size(); i++)
	{
		if (pgon_list[i].checkTrianglesHit(r))
		{
			unstd::Colour colour = pgon_list[i].triangle_list[pgon_list[i].lastHitTri()].colour;

			unstd::Vector3<float> _colour = colour.getColour();

			return _colour;

			// return unstd::Vector3<float>(1.0, 0.0, 1.0);			
		}

		unstd::Vector3<> unit_dir = unit_vector(r.direction());
		float t = 0.5f * (unit_dir.y() + 1.0f);
		return (1.0f - t) * background_colour_a + // white
						t * background_colour_b; // black
	}

	return unstd::Vector3<float>();
}
