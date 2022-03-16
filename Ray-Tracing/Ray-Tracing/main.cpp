#include "polygon.h"
#include "sphere.h"
#include "camera.h"
#include "timer.h"

#include <memory>
#include <fstream>

typedef std::vector<std::unique_ptr<object>> objects_t;

static void render(const objects_t& objects, image_t& img, const camera cam)
{
	timer t("Render");
	std::cout << "Starting render loop..." << std::endl;

	// Render loop
	for (size_t h = 0; h < IMAGE_HEIGHT; h++)
	{
		//std::cout << h << std::endl;
		for (size_t w = 0; w < IMAGE_WIDTH; w++)
		{
			const floating_point_t u = floating_point_t(w) / floating_point_t(IMAGE_WIDTH - 1);
			const floating_point_t v = floating_point_t(h) / floating_point_t(IMAGE_HEIGHT - 1);
			const ray_t ray(cam.getOrigin(), cam.getLLC() + u * cam.getHorizontal() + v * cam.getVertical() - cam.getOrigin());
			
			img[IMAGE_WIDTH * h + w] = WHITE;
			for (const auto& object : objects)
			{
				std::optional<colour_t> colour = object->get_colour(ray);
				if (colour.has_value())
				{
					img[IMAGE_WIDTH * h + w] = colour.value();
					break;
				}

			}
		}
	}

	std::cout << "Render finished." << std::endl;
}

static bool load_objects(objects_t& objects)
{
	// Pushes back a sphere
#if 0
	{
		std::unique_ptr<sphere> obj = std::make_unique<sphere>(2.5);
		obj->set_centre({ -5.0, 0.0, -10.0 });

		objects.emplace_back(std::move(obj));
	}
#endif

	// Pushes back a cow
#if 1
	{
		std::unique_ptr<polygon> obj = std::make_unique<polygon>();

		std::fstream fs("cow.obj");
		if (!fs)
			return false;

		fs >> *obj;
		obj->set_centre({ 3.0, 0.0, -10.0 });

		objects.emplace_back(std::move(obj));
	}
#endif

	// Pushes back a teapot
#if 1
	{
		std::unique_ptr<polygon> obj = std::make_unique<polygon>();

		std::fstream fs("teapot.obj");
		if (!fs)
			return false;

		fs >> *obj;
		obj->set_centre({ -3.0, 0.0, -10.0 });

		objects.emplace_back(std::move(obj));
	}
#endif

	return true;
}

int main()
{
	// Creates an objects vector and loads it up
	objects_t objects;
	if (!load_objects(objects))
		return 1;

	// Too big to be allocated on the stack
	std::unique_ptr<image_t> img = std::make_unique<image_t>();

	// Camera 
	camera cam1;

	// Does the rendering
	render(objects, *img, cam1);

	// Outputs the rendered PPM
	std::ofstream of("output.ppm");
	of << *img;

	return 0;
}