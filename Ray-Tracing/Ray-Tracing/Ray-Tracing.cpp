#include "Ray.h"
#include "Utils.h"
#include "Config.h"
#include "Polygon.h"
#include "Sphere.h"
#include "Scene.h"
#include "Camera.h"

#include <cstdint>
#include <fstream>
#include <chrono>

static image_t image;

unstd::Scene scene;

unstd::Sphere ball(1.0f);

unstd::Polygon pgon(unstd::Vector3<float>(0.0, 0.0, -5.0));

//unstd::Vector3<float> ray_colour(const unstd::Ray& r, unstd::Polygon& pgon)
//{
//	const unstd::Vector3<float> background_colour_a = unstd::Vector3<float>(1.0, 1.0, 1.0);
//	const unstd::Vector3<float> background_colour_b = unstd::Vector3<float>(0.0, 0.0, 0.0);
//
//	if (pgon.checkTrianglesHit(r)) 
//	{ 
//		return unstd::Vector3<float>(1.0, 0.0, 1.0); 
//	}
//
//	unstd::Vector3<> unit_dir = unit_vector(r.direction());
//	float t = 0.5f * (unit_dir.y() + 1.0f);
//	return (1.0f - t) * background_colour_a + // white
//					t * background_colour_b; // black
//
//
//
//}

//Render.
void render(unstd::Camera& cam)
{
	//For each pixel I need an RGB value.
	//Each pixel will be an RGB triplet.              
	for (size_t h = 0; h < IMAGE_HEIGHT; h++)
	{
		for (size_t w = 0; w < IMAGE_WIDTH; w++)
		{
			float u = float(w) / (IMAGE_WIDTH - 1);
			float v = float(h) / (IMAGE_HEIGHT - 1);

			unstd::Ray r = unstd::Ray(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
			unstd::Vector3<float> pixel_colour = scene.renderScene(r);

			pixel_t& pixel = image[IMAGE_WIDTH * h + w];
			pixel.e[0] = pixel_colour.x() * unstd::unsigned_max<colour_t>();
			pixel.e[1] = pixel_colour.y() * unstd::unsigned_max<colour_t>();
			pixel.e[2] = pixel_colour.z() * unstd::unsigned_max<colour_t>();
		}
	}

	std::ofstream of("Render_Output.ppm");
	of << image;
}

int main()
{
	unstd::Camera cam1;

	std::ifstream is("cow.obj");
	if (!is) { std::cerr << "File not found.\n"; return 1; }
	is >> pgon;

	scene.addPgonElement(pgon);
	scene.addSphereElement(ball);

	render(cam1);

	return 0;
}