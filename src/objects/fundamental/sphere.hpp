#pragma once

#include "objects/fundamental/fundamental_object.hpp"

class sphere : public fundamental_object
{
public:
    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;
    
    boundary get_boundary() const override;
    
    void set_scale(floating_point_t scale) override;
    floating_point_t get_scale() const override;
    
    void rotate(floating_point_t a, floating_point_t b, floating_point_t c) override;

    floating_point_t radius;
};