#include "complex_polygon.hpp"

#include <algorithm>

static bool size_compare(const triangle& i, const triangle& j)
{
    return i.get_area() < j.get_area();
}

static std::vector<polygon::triangles_t> stack(polygon::triangles_t&& triangles)
{
    std::vector<polygon::triangles_t> ret;
    
    // Dumb fragmentation in same order the triangles already are
   constexpr size_t fragments = 100;
   while (!triangles.empty())
        if (auto& fragment = ret.emplace_back(); triangles.size() < fragments)
        {
            fragment = std::forward<polygon::triangles_t>(triangles);
        }
        else
        {
            fragment.assign(triangles.begin(), triangles.begin() + fragments);
            triangles.erase(triangles.begin(), triangles.begin() + fragments);
        }
   
   return ret;
}

static std::vector<polygon::triangles_t> sort_then_stack(polygon::triangles_t&& triangles)
{
    // Sort the triangles by size and then do a stack
    std::sort(triangles.begin(), triangles.end(), size_compare);
    
    return stack(std::forward<polygon::triangles_t>(triangles));
}

static std::vector<polygon::triangles_t> octant(polygon::triangles_t&& triangles)
{
    std::vector<polygon::triangles_t> ret;
    
    // Find the centre of all the triangles
    spacial_t centre = { 0, 0, 0 };
    for (const auto& triangle : triangles)
        centre += triangle.get_centre();
    centre /= triangles.size();
    
    // Split the polygon into 8 Cartesian segments about the centre
    ret.resize(8);
    for (const auto& triangle : triangles)
    {
        const auto& c = triangle.get_centre();
        const size_t i = 1*(c[0] < centre[0] ? 1 : 0)
                + 2*(c[1] < centre[1] ? 1 : 0)
                + 4*(c[2] < centre[2] ? 1 : 0);
        ret[i].emplace_back(triangle);
    }
    
    // Removes any segments that are empty
    std::erase_if(ret, [](const auto& i) { return i.empty() ; }); 
    
   return ret;
}

static std::vector<polygon::triangles_t> recursive_octant(polygon::triangles_t&& triangles, bool (*predicate)(const polygon::triangles_t&))
{
    std::vector<polygon::triangles_t> ret;
    
    // Recursively octants until the predicate it met
    if (predicate(triangles))
    {
        ret.emplace_back(std::forward<polygon::triangles_t>(triangles));
    }
    else
    {
        auto once = octant(std::forward<polygon::triangles_t>(triangles));
        for (auto& i : once)
        {
            const auto recurse = recursive_octant(std::forward<polygon::triangles_t>(i), predicate);
            ret.insert(ret.end(), std::make_move_iterator(recurse.begin()), std::make_move_iterator(recurse.end()));
        }
    }
    
   return ret;
}

static std::vector<polygon::triangles_t> fragment_triangles(polygon::triangles_t&& triangles)
{
#if 1
    constexpr size_t fragments = 1000;
    return recursive_octant(std::forward<polygon::triangles_t>(triangles), [](const auto& i) { return i.size() < fragments; });
#elif 0
    return octant(std::forward<polygon::triangles_t>(triangles));
#elif 0
    return sort_then_stack(std::forward<polygon::triangles_t>(triangles));
#else
    return stack(std::forward<polygon::triangles_t>(triangles));
#endif
}

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
   
    // Fragment this polygon into triangle pieces
    const auto fragments = fragment_triangles(std::move(p.get_triangles()));
    for (auto& i : fragments)
    {
        auto& fragment = v._polygons.emplace_back();
        fragment.get_triangles() = std::move(i);
        
        // DEBUG
        fragment.set_colour(fragment.get_colour());
    }
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const complex_polygon& v)
{
    return os;
}