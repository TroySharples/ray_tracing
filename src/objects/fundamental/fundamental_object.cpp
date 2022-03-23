#include "fundamental_object.hpp"

static colour_t calculate_shader(const colour_t& colour, floating_point_t alignment)
{
    return colour*alignment;
}

static spacial_t calculate_reflection(const spacial_t& direction, const spacial_t& normal, floating_point_t alignment, floating_point_t roughness)
{
    spacial_t ret = direction - 2*alignment*normal;
    
#if 1
    ret += unstd::cross_product(normal, random_spacial(roughness*ret.length()));
#endif    
    
    return ret.normalise();
}

static floating_point_t calculate_transparency(floating_point_t alignment, floating_point_t reflectivity)
{
    return alignment*reflectivity;
}

object::hit_info fundamental_object::calculate_hit_info(const spacial_t& intersection, const spacial_t& direction, const spacial_t& normal, floating_point_t z2) const
{
    // We weren't given the alignment so we have to calculate it ourselves here
    return calculate_hit_info(intersection, direction, normal, z2, unstd::dot_product(normal, direction));
}      

object::hit_info fundamental_object::calculate_hit_info(const spacial_t& intersection, const spacial_t& direction, const spacial_t& normal, floating_point_t z2, floating_point_t alignment) const
{
    return { calculate_shader(mat.colour, alignment), z2, mat.albedo, calculate_transparency(alignment, mat.reflectivity), { intersection, calculate_reflection(direction, normal, alignment, mat.roughness) } };
}    