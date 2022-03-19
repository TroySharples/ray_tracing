#include "renderer.h"

#include "objects/object.h"

void renderer::render(const objects_t& objects, image_t& img, const camera cam)
{
	life_timer t("Render");
	std::cout << "Starting render loop..." << std::endl;

	// Render loop
	for (size_t h = 0; h < IMAGE_HEIGHT; h++)
	{
		//std::cout << h << std::endl;
		for (size_t w = 0; w < IMAGE_WIDTH; w++)
		{
			const floating_point_t u = floating_point_t(w) / floating_point_t(IMAGE_WIDTH - 1);
			const floating_point_t v = floating_point_t(h) / floating_point_t(IMAGE_HEIGHT - 1);
			ray_t ray(
				cam.getOrigin(),
				cam.getLLC() + u *
				cam.getHorizontal() + v *
				cam.getVertical() - cam.getOrigin());

			ray.direction.normalise();

			std::optional<object::hit_info> pixel;

			// Default pixel colour WHITE
			img[IMAGE_WIDTH * h + w] = BLACK;
			for (const auto& object : objects)
			{
				auto h_i = object->get_hit_info(ray);
				if (h_i.has_value() &&
					(!pixel.has_value() ||
					pixel.value().z > h_i.value().z))
				{
					img[IMAGE_WIDTH * h + w] = h_i.value().colour;
				}
			}
		}
	}

	std::cout << "Render finished." << std::endl;
}
