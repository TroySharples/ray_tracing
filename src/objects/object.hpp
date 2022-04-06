#pragma once

#include "config.hpp"

#include <optional>

class object
{
public:
    virtual ~object() = default;

    struct hit_info
    {
        colour_t colour;
        floating_point_t alignment;
        floating_point_t brightness;
        floating_point_t reflectivity;
        floating_point_t transparency;
        floating_point_t roughness;
        floating_point_t z2;
        spacial_t intersection;
        spacial_t reflection;
        spacial_t refraction;
    };

    virtual std::optional<hit_info> get_hit_info(const ray_t& ray) const = 0;
    
    struct boundary
    {
        spacial_t min;
        spacial_t max;
    };
    
    virtual boundary get_boundary() const = 0;

    virtual void set_centre(spacial_t centre) { _centre = centre; }
    const spacial_t get_centre() const { return _centre; }
    
    virtual void set_scale(floating_point_t scale) = 0;
    virtual floating_point_t get_scale() const = 0;
    
    void enlarge(floating_point_t factor) { set_scale(factor*get_scale()); }
    
    virtual void rotate(floating_point_t a, floating_point_t b, floating_point_t c) = 0;

protected:
    spacial_t _centre{ 0, 0, 0 };
};
