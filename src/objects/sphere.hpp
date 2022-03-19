#pragma once

#include "object.hpp"

class sphere : public object
{
public:
    sphere(floating_point_t radius_);

    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    colour_t colour = random_colour();
    floating_point_t radius;
};