#include "Ray.h"
#include "Utils.h"
#include "Config.h"
#include "Polygon.h"
#include "Sphere.h"

#include <cstdint>
#include <fstream>

static image_t image;

unstd::Vector3<float> ray_colour(const unstd::Ray& r, const unstd::Object& obj)
{
	if (obj.hit(unstd::Vector3<float>(0.0, 0.0, -2.5), r)) { return unstd::Vector3<float>(1.0, 0.0, 0.0); }

	unstd::Vector3<> unit_dir = unit_vector(r.direction());
	float t = 0.5f * (unit_dir.y() + 1.0f);
	return (1.0f - t) * unstd::Vector3<float>(1.0, 1.0, 1.0) + // white
		t * unstd::Vector3<float>(0.0, 0.0, 0.0); // black
}

// render(scene, camera) { return image; }
void render()
{
	unstd::Sphere bob(0.5f);	

	// Camera.
	float cam_height = 2.0;
	float cam_width = ASPECT_RATIO * cam_height;
	float focal_length = 1.0;

	unstd::Vector3<float> origin = unstd::Vector3<float>(0, 0, 0);
	unstd::Vector3<float> horizontal = unstd::Vector3<float>(cam_width, 0, 0);
	unstd::Vector3<float> vertical = unstd::Vector3<float>(0, cam_height, 0);
	unstd::Vector3<float> lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - unstd::Vector3<float>(0, 0, focal_length);

	//Render.
	//For each pixel I need an RGB value.
	//Each pixel will be an RGB triplet.

	for (size_t h = 0; h < IMAGE_HEIGHT; h++)
	{
		for (size_t w = 0; w < IMAGE_WIDTH; w++)
		{
			//pixel_t& pixel = image[IMAGE_WIDTH * h + w];
			//pixel.e[0] = h * unsigned_max<colour_t>() / IMAGE_HEIGHT;
			//pixel.e[1] = w * unsigned_max<colour_t>() / IMAGE_WIDTH;
			//pixel.e[2] = 0.25 * unsigned_max<colour_t>();

			float u = float(w) / (IMAGE_WIDTH - 1);
			float v = float(h) / (IMAGE_HEIGHT - 1);

			unstd::Ray r = unstd::Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			unstd::Vector3<float> pixel_colour = ray_colour(r, bob);

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
	render();

	unstd::Polygon p;
	std::ifstream is("cube.obj");
	if (!is) { std::cerr << "File not found.\n"; return 1; }
	is >> p;

	return 0;
}