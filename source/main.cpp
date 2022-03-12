#include "polygon.h"
#include "sphere.h"

#include <memory>
#include <fstream>

typedef std::vector<std::unique_ptr<object>> objects_t;

static void render(const objects_t& objects, image_t& img)
{
	// Camera
	constexpr floating_point_t cam_height = floating_point_t(2.0);
	constexpr floating_point_t cam_width = ASPECT_RATIO * cam_height;
	constexpr floating_point_t focal_length = floating_point_t(1.0);

	constexpr spacial_t origin = { 0, 0, 0 };
	constexpr spacial_t horizontal = { cam_width, 0, 0 };
	constexpr spacial_t vertical = { 0 , cam_height, 0 };
	constexpr spacial_t lower_left_corner = origin - horizontal / floating_point_t(2.0) - vertical / floating_point_t(2.0) - spacial_t({ 0, 0, focal_length });

	// Render loop
	for (size_t h = 0; h < IMAGE_HEIGHT; h++)
	{
		for (size_t w = 0; w < IMAGE_WIDTH; w++)
		{
			const floating_point_t u = floating_point_t(w) / floating_point_t(IMAGE_WIDTH - 1);
			const floating_point_t v = floating_point_t(h) / floating_point_t(IMAGE_HEIGHT - 1);
			const ray_t ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			
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
		obj->set_centre({ 2.0, 0.0, -5.0 });

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
		obj->set_centre({ -7.0, 0.0, -7.0 });

		objects.emplace_back(std::move(obj));
	}
#endif

	// Pushes back a parallelogram
#if 0
	{
		std::unique_ptr<parallelogram> obj = std::make_unique<parallelogram>();
		(*obj)[0] = { 0.0, 0.0, -5.0 };
		(*obj)[1] = { 0.0, 1.0, -5.0 };
		(*obj)[2] = { 1.0, 1.0, -5.0 };

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

	// Does the rendering
	render(objects, *img);

	// Outputs the rendered PPM
	std::ofstream of("output.ppm");
	of << *img;

	return 0;
}