#include "sphere.hpp"

sphere::sphere(floating_point_t radius_)
    : radius(radius_)
{

}

std::optional<object::hit_info> sphere::get_hit_info(const ray_t& ray) const
{    
    const spacial_t oc = ray.origin - _centre;
    const floating_point_t oc_dot_n = unstd::dot_product(oc, ray.direction);
    const floating_point_t alignment = (oc.square_length() - std::pow(oc_dot_n, 2))/std::pow(radius, 2);

    return alignment < 1 ? hit_info(colour*std::cos(M_PI*alignment/2), oc.length() - radius, ray_t()) : std::optional<hit_info>();
}