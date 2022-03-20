#include <future>

#include "render.hpp"

#include "utils/timer.hpp"
#include "objects/object.hpp"

#include <future>

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

static void fill_image(const objects_t& objects, const camera& cam, image_t& img)
{    
    // Render loop
    for (size_t h = 0; h < IMAGE_HEIGHT; h++)
    {
        for (size_t w = 0; w < IMAGE_WIDTH; w++)
        {
            const floating_point_t u = floating_point_t(w) / floating_point_t(IMAGE_WIDTH - 1);
            const floating_point_t v = floating_point_t(h) / floating_point_t(IMAGE_HEIGHT - 1);
            
            constexpr floating_point_t fuzz = std::min(camera::cam_width/IMAGE_WIDTH, camera::cam_height/IMAGE_HEIGHT);
            
            // Make the ray
            ray_t ray(cam.origin, cam.lower_left_corner + u*cam.horizontal + v*cam.vertical - cam.origin);
            ray.direction += random_spacial(fuzz);
            ray.direction.normalise();
            
            img[IMAGE_WIDTH * h + w] = get_colour(objects, ray);
        }
    }
}

void rendering::render(const objects_t& objects, const camera& cam, image_t& img)
{
    life_timer t("render loop");
    
    // Creates a set of images for FXAA. We allocate the images on the heap because they are too big for the stack
    std::array<std::unique_ptr<image_t>, FXAA> images;
    
    // Create a different thread using async for each FXAA pass
    {
        std::array<std::future<void>, FXAA> futures;
        for (size_t i = 0; i < FXAA; i++)
        {
            images[i] = std::make_unique<image_t>();
            futures[i] = std::async(std::launch::async, fill_image, std::ref(objects), std::ref(cam), std::ref(*images[i]));
        }
    }
    
    // Makes the final image as an average of the FXAA images
    for (size_t i = 0; i < std::size(img); i++)
    {
        colour_t colour = {0, 0, 0};
        for (const auto& image : images)
            colour += ((*image)[i] / floating_point_t(FXAA));
        img[i] = colour;
    }
}
