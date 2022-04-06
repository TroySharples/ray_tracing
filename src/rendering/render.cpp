#include <future>

#include "render.hpp"

#include "utils/timer.hpp"
#include "objects/object.hpp"

#include <future>

using namespace rendering;

template <typename... _T>
static colour_t average_colours(const _T&... t)
{
    colour_t ret = { 0 };
    ((ret += t/floating_point_t(sizeof...(_T))), ...);
    
    return ret;
}

static floating_point_t black_body_shader(floating_point_t alignment)
{
    return std::abs(alignment);
}

static floating_point_t reflection_shader(floating_point_t alignment)
{
#if 0
    return 1.0 - 0.5*std::abs(alignment);
#else
    return 0.8;
#endif
}

static floating_point_t refraction_shader(floating_point_t alignment)
{
#if 0
    return 0.5 +  0.5*std::abs(alignment);
#else
    return 0.8;
#endif
}

static colour_t get_colour(const object& obj, const ray_t& ray, floating_point_t contribution = 1.0)
{    
    // Set the default colour (the colour of rays that don't hit the object)
    colour_t ret = BACKGROUND_COLOUR;
    
    // Return if we are too deep (our returned colour will affect the brightness of the pixel by less than 1%)
    if (contribution < DEPTH_THRESHOLD)
        return ret;
    
    // See if we hit the object
    std::optional<object::hit_info> info = obj.get_hit_info(ray);
        
    // Return if we didn't hit anything
    if (!info.has_value())
        return ret;
    object::hit_info& hit = info.value();
    
    // Calculate the colour mixing coefficients
    const floating_point_t black_body_coefficient = black_body_shader(hit.alignment)*hit.brightness;
    const floating_point_t reflection_coefficient = reflection_shader(hit.alignment)*hit.reflectivity;
    const floating_point_t refraction_coefficient = refraction_shader(hit.alignment)*hit.transparency;
            
    // Calculate the colour
    ret = average_colours(hit.colour*black_body_coefficient, 
            get_colour(obj, { hit.intersection, hit.reflection.normalise(), ray.orientation }, contribution*reflection_coefficient)*reflection_coefficient,
            get_colour(obj, { hit.intersection, hit.refraction.normalise(), !ray.orientation }, contribution*refraction_coefficient)*refraction_coefficient);
        
    return ret;
}

void rendering::render(const object& obj, const camera& cam, image_t& img)
{    
    // Render loop
    for (size_t h = 0; h < IMAGE_HEIGHT; h++)
    {
        for (size_t w = 0; w < IMAGE_WIDTH; w++)
        {
            const floating_point_t u = floating_point_t(w) / floating_point_t(IMAGE_WIDTH - 1);
            const floating_point_t v = floating_point_t(h) / floating_point_t(IMAGE_HEIGHT - 1);
            
            constexpr floating_point_t fuzz = 0.25*std::min(camera::cam_width/IMAGE_WIDTH, camera::cam_height/IMAGE_HEIGHT);
            
            // Make the ray
            ray_t ray(cam.origin, cam.upper_left_corner + u*cam.horizontal - v*cam.vertical - cam.origin);
            ray.direction += unstd::cross_product(ray.direction, random_spacial(fuzz));
            ray.direction.normalise();
            
            img[IMAGE_WIDTH * h + w] = get_colour(obj, ray);
        }
    }
}

void rendering::render_msaa(const object& obj, const camera& cam, image_t& img)
{
    life_timer t("render loop");
    
    // Creates a set of images for MSAA. We allocate the images on the heap because they are too big for the stack
    std::array<std::unique_ptr<image_t>, MSAA> images;
    
    // Create a different thread using async for each MSAA pass
    {
        std::array<std::future<void>, MSAA> futures;
        for (size_t i = 0; i < MSAA; i++)
        {
            images[i] = std::make_unique<image_t>();
            futures[i] = std::async(std::launch::async, render, std::ref(obj), std::ref(cam), std::ref(*images[i]));
        }
    }
    
    // Makes the final image as an average of the MSAA images
    for (size_t i = 0; i < std::size(img); i++)
    {
        // We change to a vector of longs (instead of rgb_ts) to create a better average
        unstd::vector<long unsigned int, 3> colour = {0, 0, 0};
        for (const auto& image : images)
            for (size_t j = 0; j < 3; j++)
                colour[j] += (*image)[i][j];
        colour /= floating_point_t(MSAA);
        
        img[i] = {rgb_t(colour[0]), rgb_t(colour[1]), rgb_t(colour[2])};
    }
}
