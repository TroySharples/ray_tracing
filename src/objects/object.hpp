#pragma once

#include "config.hpp"

#include <optional>

class object
{
public:
    virtual ~object() = default;

    struct hit_info
    {
        hit_info() = default;
        hit_info(const colour_t& col_, floating_point_t z2_, floating_point_t albedo_, floating_point_t transparency_, const ray_t& next_ray_) 
                : colour(col_), z2(z2_), albedo(albedo_), transparency(transparency_), next_ray(next_ray_) { }

        colour_t colour;
        floating_point_t z2;
        floating_point_t albedo;
        floating_point_t transparency;
        ray_t next_ray;
    };

    virtual std::optional<hit_info> get_hit_info(const ray_t& ray) const = 0;

    virtual void set_centre(const spacial_t& centre) { _centre = centre; }
    const spacial_t& get_centre() const { return _centre; }

protected:
    spacial_t _centre{ 0, 0, 0 };
};
