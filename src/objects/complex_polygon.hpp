#pragma once

#include "polygon.hpp"

class complex_polygon : public object
{
public:
    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

    void set_centre(const spacial_t& centre) override;
    
    void set_colour(const colour_t& colour);
    const colour_t& get_colour() const { return _colour; }

private:
    typedef std::vector<polygon> polygons_t;
    polygons_t _polygons;
    
    colour_t _colour = random_colour();
    
    friend std::istream& operator>>(std::istream& is, complex_polygon& v);
    friend std::ostream& operator<<(std::ostream& os, const complex_polygon& v);
};