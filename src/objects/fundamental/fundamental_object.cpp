#include "fundamental_object.hpp"

static spacial_t calculate_reflection(const spacial_t& direction, const spacial_t& normal, floating_point_t alignment)
{
//    ret += unstd::cross_product(normal, random_spacial(roughness*ret.length()));
    return direction + 2*alignment*normal;
}

static spacial_t calculate_refraction(const spacial_t& direction, const spacial_t& normal, floating_point_t alignment, floating_point_t refractive_index)
{
    // For now ignore the actual refractive effect
//    return direction -2*alignment*refractive_index*normal;
    return direction;
}

object::hit_info fundamental_object::calculate_hit_info(const spacial_t& intersection, const spacial_t& direction, const spacial_t& normal, floating_point_t z2) const
{
    // We weren't given the alignment so we have to calculate it ourselves here
    return calculate_hit_info(intersection, direction, normal, z2, -unstd::dot_product(normal, direction));
}      

object::hit_info fundamental_object::calculate_hit_info(const spacial_t& intersection, const spacial_t& direction, const spacial_t& normal, floating_point_t z2, floating_point_t alignment) const
{
    return { mat.colour, alignment, mat.brightness, mat.reflectivity, mat.transparancy, mat.roughness, z2, intersection, calculate_reflection(direction, normal, alignment), calculate_refraction(direction, normal, alignment, mat.refractive_index) };
}    