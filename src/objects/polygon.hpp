#pragma once

#include "triangle.hpp"
#include "parallelepiped.hpp"

#include <vector>

class polygon : public object
{
public:
    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    void set_centre(const spacial_t& centre) override;
    
    void set_colour(const colour_t& colour);
    const colour_t& get_colour() const { return _colour; }

private:
    typedef std::vector<triangle> triangles_t;
    triangles_t _triangles;
    
    colour_t _colour = random_colour();

    mutable std::optional<parallelepiped> _bounding_box;

    friend std::istream& operator>>(std::istream& is, polygon& v);
    friend std::ostream& operator<<(std::ostream& os, const polygon& v);

private:
    void make_bounding_box() const;
};