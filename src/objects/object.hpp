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
        floating_point_t z2;
        floating_point_t albedo;
        floating_point_t transparency;
        ray_t next_ray;
    };

    virtual std::optional<hit_info> get_hit_info(const ray_t& ray) const = 0;

    virtual void set_centre(spacial_t centre) { _centre = centre; }
    const spacial_t get_centre() const { return _centre; }
    
    virtual void set_scale(floating_point_t scale) = 0;
    virtual floating_point_t get_scale() const = 0;
    
    void enlarge(floating_point_t factor) { set_scale(factor*get_scale()); }

protected:
    spacial_t _centre{ 0, 0, 0 };
};
