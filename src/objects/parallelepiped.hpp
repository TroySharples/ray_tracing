#pragma once

#include "objects/fundamental/parallelogram.hpp"

class parallelepiped: public object
{
public:
    parallelepiped() = default;
    parallelepiped(const spacial_t& x, const spacial_t& y, const spacial_t& z);

    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    void set_centre(const spacial_t& centre) override;
    
    floating_point_t get_volume() const;
    spacial_t get_centre() const;

private:
    typedef std::array<parallelogram, 6> parallelograms_t;
    parallelograms_t _parallelograms;
};