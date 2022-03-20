#include "render.hpp"

#include "utils/timer.hpp"

#include "objects/object.hpp"

using namespace rendering;

static colour_t mix_colours(const colour_t& colour1, const colour_t& colour2, floating_point_t albedo)
{
    return colour1*(1 - albedo) + colour2*albedo*albedo;
}

static colour_t get_colour(const objects_t& objects, const ray_t& ray, size_t depth = 0)
{    
    // Set the default colour (the colour of rays that don't hit the object)
    colour_t ret = BACKGROUND_COLOUR;
    
    // Return if we are too deep
    if (depth > MAX_SCATTER_DEPTH)
        return ret;
    
    // Loop over all the objects and set the final hit info to be the closest hit
    std::optional<object::hit_info> info;
    for (const auto& object : objects)
        if (const auto i = object->get_hit_info(ray); i.has_value() && (!info.has_value() || info.value().z2 > i.value().z2))
            info = i.value();
        
    if (info.has_value())
        ret = mix_colours(info.value().colour, get_colour(objects, info.value().next_ray, ++depth), info.value().albedo);
        
    return ret;
}

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
            
            img[IMAGE_WIDTH * h + w] = get_colour(objects, ray);
        }
    }
}
