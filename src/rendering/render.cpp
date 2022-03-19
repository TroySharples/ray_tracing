#include "render.hpp"

#include "utils/timer.hpp"

#include "objects/object.hpp"

void rendering::render(const objects_t& objects, const camera& cam, image_t& img)
{
    life_timer t("render loop");
    
    // Render loop
    for (size_t h = 0; h < IMAGE_HEIGHT; h++)
    {
        //std::cout << h << std::endl;
        for (size_t w = 0; w < IMAGE_WIDTH; w++)
        {
            const floating_point_t u = floating_point_t(w) / floating_point_t(IMAGE_WIDTH - 1);
            const floating_point_t v = floating_point_t(h) / floating_point_t(IMAGE_HEIGHT - 1);
            
            // Make the ray
            ray_t ray(
                cam.getOrigin(),
                cam.getLLC() + u *
                cam.getHorizontal() + v *
                cam.getVertical() - cam.getOrigin());
            ray.direction.normalise();
            
            // Loop over all the objects and set the final hit info to be the closest hit
            std::optional<object::hit_info> info;
            for (const auto& object : objects)
            {
                auto i = object->get_hit_info(ray);
                if (i.has_value() && (!info.has_value() || info.value().z > i.value().z))
                    info = i.value();
            }
            
            // Set this pixel in the image to the colour of the final hit info if it exists and to BLACK otherwise
            img[IMAGE_WIDTH * h + w] = info.has_value() ? info.value().colour : BLACK;
        }
    }
}
