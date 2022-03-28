#include "sphere.hpp"

#include "utils/logging.hpp"

std::optional<object::hit_info> sphere::get_hit_info(const ray_t& ray) const
{    
    std::optional<hit_info> ret;
    
    const spacial_t oc = _centre - ray.origin;
    const floating_point_t oc_dot_n = unstd::dot_product(oc, ray.direction);
    const floating_point_t alignment = (oc.square_length() - std::pow(oc_dot_n, 2))/std::pow(radius, 2);

    // Return if we didn't hit
    if (alignment > 1 - EPSILON)
        return ret;
    
    // Compute the distance along the ray which intersects with the plane
    const floating_point_t t = oc_dot_n - std::sqrt((1 - alignment)*std::pow(radius, 2));
    
    // If t is negative the triangle is behind the camera
    if (t < EPSILON) return ret;
    
    // We hit if we made it here
    const spacial_t intersection = ray[t];
    const spacial_t normal = intersection - _centre;
    ret = calculate_hit_info(intersection, ray.direction, normal, std::pow(t, 2), std::cos(M_PI*alignment/2));
    
    return ret;
}

void sphere::set_scale(floating_point_t scale) 
{ 
    radius = scale; 
}

floating_point_t sphere::get_scale() const
{ 
    return radius; 
}

void sphere::rotate(floating_point_t a, floating_point_t b, floating_point_t c)
{
    // Spheres are symmetrical so we don't have to do anything
}