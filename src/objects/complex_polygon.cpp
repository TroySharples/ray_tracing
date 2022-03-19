#include "complex_polygon.hpp"


std::optional<object::hit_info> complex_polygon::get_hit_info(const ray_t& ray) const
{
    std::optional<hit_info> ret;
    for (const auto& i : _polygons)
    {
        const auto info = i.get_hit_info(ray);
        if (info.has_value() && (!ret.has_value() || ret.value().z > info.value().z))
            ret = info;
    }

    return ret;
}

void complex_polygon::set_centre(const spacial_t& centre)
{
    _centre = centre;
    for (auto& i : _polygons)
        i.set_centre(centre);
}

void complex_polygon::set_colour(const colour_t& colour)
{
    _colour = colour;
    for (auto& i : _polygons)
        i.set_colour(colour);
}

std::istream& operator>>(std::istream& is, complex_polygon& v)
{
    // First create a normal polygon and read everything into it
    polygon p;
   is >> p;
    
   constexpr size_t fragments = 10;
   
    // Fragment this polygon into triangle pieces
    auto& triangles = p.get_triangles();
    while (!triangles.empty())
    {
        v._polygons.emplace_back();
        auto& fragment = v._polygons.back().get_triangles();
        if (triangles.size() < fragments)
        {
            fragment = std::move(triangles);
        }
        else
        {
            fragment.assign(triangles.begin(), triangles.begin() + fragments);
            triangles.erase(triangles.begin(), triangles.begin() + fragments);
        }
        
        // DEBUG
        v._polygons.back().set_colour(v._polygons.back().get_colour());
    }
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const complex_polygon& v)
{
    return os;
}