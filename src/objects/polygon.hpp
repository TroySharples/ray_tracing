#pragma once

#include "triangle.hpp"
#include "parallelepiped.hpp"

#include <vector>

class polygon : public object
{
public:
    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    typedef std::vector<triangle> triangles_t;
    triangles_t& get_triangles();
    const triangles_t& get_triangles() const;

    void set_centre(const spacial_t& centre) override;
    
    void set_material(const material& mat);
    const material& get_material() const { return _mat; }
    
private:
    triangles_t _triangles;
    mutable std::optional<parallelepiped> _bounding_box;
    
    material _mat;

    friend std::istream& operator>>(std::istream& is, polygon& v);
    friend std::ostream& operator<<(std::ostream& os, const polygon& v);

private:
    void make_bounding_box() const;
};