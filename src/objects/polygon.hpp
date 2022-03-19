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
    
    void set_colour(const colour_t& colour);
    const colour_t& get_colour() const { return _colour; }
    
private:
    triangles_t _triangles;
    mutable std::optional<parallelepiped> _bounding_box;
    
    colour_t _colour = random_colour();

    friend std::istream& operator>>(std::istream& is, polygon& v);
    friend std::ostream& operator<<(std::ostream& os, const polygon& v);

private:
    void make_bounding_box() const;
};