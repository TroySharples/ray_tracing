#include "sphere.hpp"

#include "utils/logging.hpp"

std::optional<object::hit_info> sphere::get_hit_info(const ray_t& ray) const
{    
    std::optional<hit_info> ret;
    
    const spacial_t oc = _centre - ray.origin;
    const floating_point_t oc_dot_d = unstd::dot_product(oc, ray.direction);
    
    // We handle whether we hit or not differently depending on whether our ray is aligned
    floating_point_t t;
    if (ray.orientation)
    {
        const floating_point_t discriminant = oc.square_length() - std::pow(oc_dot_d, 2);

        // Return if we didn't hit
        if (discriminant > std::pow(radius, 2) - EPSILON)
            return ret;
        
        // Compute the distance along the ray which intersects with the plane
        t = oc_dot_d - std::sqrt((std::pow(radius, 2) - discriminant));
    }
    else
    {
        // Return if we are not already inside this sphere. We add a EPSILON buffer as most of these rays will be coming from an inbound ray originating from the spheres surface so we would expect
        // OC have a length of radius exactly
        if (oc.square_length() > std::pow(radius, 2) + EPSILON)
            return ret;
        
        t = 2.0*oc_dot_d;
    }
    
    // If t is negative the sphere is behind the camera
    if (t < EPSILON) return ret;
    
    // We hit if we made it here
    const spacial_t intersection = ray[t];
    const spacial_t normal = (intersection - _centre).normalise();
    ret = calculate_hit_info(intersection, ray.direction, normal, std::pow(t, 2));
    
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