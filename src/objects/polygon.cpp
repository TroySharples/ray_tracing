#include "polygon.hpp"

#include <sstream>

std::optional<object::hit_info> polygon::get_hit_info(const ray_t& ray) const
{
    std::optional<hit_info> ret;
    
    // Make our bounding box if we haven't already
    if (!_bounding_box.has_value())
        make_bounding_box();
    const parallelepiped& bounding_box = _bounding_box.value();

    // Return false straight away if we don't hit the bounding box
    const auto info = bounding_box.get_hit_info(ray);
    if (!info.has_value())
        return ret;

#if 1
    // Render the triangles
    for (const auto& i : _triangles)
    {
        const auto info = i.get_hit_info(ray);
        if (info.has_value() && (!ret.has_value() || ret.value().z2 > info.value().z2))
            ret = info;
    }
#endif
    
#if 0
    // Return a glass-like texture if we miss the polygon but hit its bounding bow
    if (!ret.has_value())
    {
        ret = info;
        ret.value().next_ray.direction = ray.direction;
    }
#endif

    return ret;
}

polygon::triangles_t& polygon::get_triangles()
{
    _bounding_box.reset();
    return _triangles;
}

const polygon::triangles_t& polygon::get_triangles() const
{
    return _triangles;
}

void polygon::set_centre(const spacial_t& centre)
{
    // Also reset centre for each of our triangles and parallelepiped as well
    _centre = centre;
    for (auto& i : _triangles)
        i.set_centre(centre);

    _bounding_box.reset();
}

void polygon::set_colour(const colour_t& colour)
{
    _colour = colour;
    for (auto& i : _triangles)
        i.colour = colour;
}

std::istream& operator>>(std::istream& is, polygon& v)
{
    std::vector<spacial_t> vertexes;
    std::vector<unstd::vector<size_t, 3>> mesh;

    // Read until the end of the file
    while (is)
    {
        // Get the prefix of the line.
        std::string prefix;
        is >> prefix;

        if (prefix == "v")
        {
            // Read the vertex positions
            vertexes.emplace_back();
            spacial_t& vertex = vertexes.back();

            is >> vertex[0] >> vertex[1] >> vertex[2];
        }
        else if (prefix == "f")
        {
            // Read the mesh (how all the vertexes are joined together to create triangles
            mesh.emplace_back();
            unstd::vector<size_t, 3>& net = mesh.back();

            // We only care about the first coordinate for now
            for (auto& i : net)
                is >> i;
        }

        // Read until the end of the line
        is.ignore(64, '\n');
    }

    // Create the triangle vector out of these
    v._triangles.clear();
    for (const auto& net : mesh)
    {
        v._triangles.emplace_back();
        auto& triangle = v._triangles.back();

        for (size_t j = 0; j < net.size(); j++)
            triangle[j] = vertexes[net[j] - 1];
    }

    // Reset the centre and colours of all the triangles
    v.set_centre(v._centre);
    v.set_colour(v._colour);

    return is;
}

std::ostream& operator<<(std::ostream& os, const polygon& v)
{
    return os;
}

void polygon::make_bounding_box() const
{
    // Just make a random bounding box if we are empty
    if (_triangles.empty())
    {
        _bounding_box = parallelepiped();
        return;
    }
        
    // Find the minimum and maximum x / y / z coordinates
    spacial_t min = _triangles[0][0];
    spacial_t max = _triangles[0][0];
    for (const auto& triangle : _triangles)
        for (const auto& vertex : triangle)
            for (size_t i = 0; i < vertex.size(); i++)
            {
                min[i] = std::min(min[i], vertex[i]);
                max[i] = std::max(max[i], vertex[i]);
            }

    // Make the diagonal vector that spans the whole polygon
    const spacial_t diagonal = max - min;

    // Make the x, y, z coordinates for the parallelepiped
    const spacial_t x = { diagonal[0], 0, 0 };
    const spacial_t y = { 0, diagonal[1], 0 };
    const spacial_t z = { 0, 0, diagonal[2] };

    // Make the parallelepiped with the centre set properly
    _bounding_box = parallelepiped(x, y, z);
    _bounding_box.value().set_centre(_centre + min);
}