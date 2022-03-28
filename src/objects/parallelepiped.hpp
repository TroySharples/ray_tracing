#pragma once

#include "objects/fundamental/parallelogram.hpp"

class parallelepiped: public object
{
public:
    parallelepiped(const spacial_t& x, const spacial_t& y, const spacial_t& z);

    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    void set_centre(spacial_t centre) override;
    
    floating_point_t get_volume() const;
    
    spacial_t get_centre() const;
    
    void set_scale(floating_point_t scale) override;
    floating_point_t get_scale() const override;
    
    void rotate(floating_point_t a, floating_point_t b, floating_point_t c) override;

private:
    typedef std::array<parallelogram, 6> parallelograms_t;
    parallelograms_t _parallelograms;
};