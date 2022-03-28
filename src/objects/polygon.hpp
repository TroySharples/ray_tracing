#pragma once

#include "objects/fundamental/triangle.hpp"
#include "objects/parallelepiped.hpp"

#include <vector>

class polygon : public object
{
public:
    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    typedef std::vector<triangle> triangles_t;
    triangles_t& get_triangles();
    const triangles_t& get_triangles() const;

    void set_centre(spacial_t centre) override;
    
    void set_scale(floating_point_t scale) override;
    floating_point_t get_scale() const override;
    
    void rotate(floating_point_t a, floating_point_t b, floating_point_t c) override;
    
    void set_material(const fundamental_object::material& mat);
    const fundamental_object::material& get_material() const { return _mat; }
    
private:
    triangles_t _triangles;
    mutable std::optional<parallelepiped> _bounding_box;
    
    fundamental_object::material _mat;

    friend std::istream& operator>>(std::istream& is, polygon& v);
    friend std::ostream& operator<<(std::ostream& os, const polygon& v);

private:
    void make_bounding_box() const;
};