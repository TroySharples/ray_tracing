#pragma once

#include "polygon.hpp"

class complex_polygon : public object
{
public:
    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    void set_centre(spacial_t centre) override;
    
    void set_scale(floating_point_t scale) override;
    floating_point_t get_scale() const override;
    
    void rotate(floating_point_t a, floating_point_t b, floating_point_t c) override;
    
    void set_material(const fundamental_object::material& mat);
    const fundamental_object::material& get_material() const { return _material; }

private:
    typedef std::vector<polygon> polygons_t;
    polygons_t _polygons;
    
    fundamental_object::material _material;
    
    friend std::istream& operator>>(std::istream& is, complex_polygon& v);
    friend std::ostream& operator<<(std::ostream& os, const complex_polygon& v);
};