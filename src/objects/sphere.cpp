#include "sphere.hpp"

#include "utils/logging.hpp"

sphere::sphere(floating_point_t radius_)
    : radius(radius_)
{

}

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
    
    // Compute the actual point of intersection and the displacement vector to this point
    const spacial_t intersection = ray[t];
    
    // The normal to the point of intersection
    const spacial_t normal = intersection - _centre;
    
    ret = hit_info(colour*std::cos(M_PI*alignment/2), (intersection - ray.origin).square_length(), ray_t(intersection, (intersection - 2*unstd::dot_product(intersection, normal)*normal).normalise()));
    
    return ret;
}