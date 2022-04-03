#pragma once

#include "objects/object.hpp"

class fundamental_object : public object
{
public:
    virtual ~fundamental_object() = default;
    
    struct material
    {
        colour_t colour = random_colour();
        floating_point_t brightness = 1.0;
        floating_point_t reflectivity = 0.0;
        floating_point_t transparancy = 1.0;
        floating_point_t roughness = 0.0;
        floating_point_t refractive_index = 0.5;
    };

    material mat;
    
protected:
    hit_info calculate_hit_info(const spacial_t& intersection, const spacial_t& direction, const spacial_t& normal, floating_point_t z2) const;
    hit_info calculate_hit_info(const spacial_t& intersection, const spacial_t& direction, const spacial_t& normal, floating_point_t z2, floating_point_t alignment) const;
};