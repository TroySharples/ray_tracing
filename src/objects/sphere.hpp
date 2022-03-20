#pragma once

#include "object.hpp"

class sphere : public object
{
public:
    sphere(floating_point_t radius_);

    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    floating_point_t radius;
    
    material mat;
};