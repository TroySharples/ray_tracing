#include "polygon.hpp"

#include <sstream>

std::optional<object::hit_info> polygon::get_hit_info(const ray_t& ray) const
{
    std::optional<hit_info> ret;
    
    // Render the triangles
    for (const auto& triangle : _triangles)
        if (const auto info = triangle.get_hit_info(ray); info.has_value() && (!ret.has_value() || ret.value().z2 > info.value().z2))
            ret = info;
    
    return ret;
}

polygon::boundary polygon::get_boundary() const
{
    // Return if we contain no triangles
    if (_triangles.empty())
        return {};
      
    boundary ret = _triangles[0].get_boundary();
    for (const auto& triangle : _triangles)
    {
        boundary b = triangle.get_boundary();
        for (size_t i = 0; i < 3; i++)
        {
            ret.min[i] = std::min(ret.min[i], b.min[i]); 
            ret.max[i] = std::max(ret.max[i], b.max[i]); 
        }
    }
    
    return ret;
}

polygon::triangles_t& polygon::get_triangles()
{
    return _triangles;
}

const polygon::triangles_t& polygon::get_triangles() const
{
    return _triangles;
}

void polygon::set_centre(spacial_t centre)
{
    // Also reset centre for each of our triangles and parallelepiped as well
    _centre = centre;
    for (auto& i : _triangles)
        i.set_centre(centre);
}

void polygon::set_scale(floating_point_t scale)
{
    const floating_point_t factor = scale / get_scale();
    for (auto& triangle : _triangles)
        triangle.enlarge(factor);
}

floating_point_t polygon::get_scale() const
{
    // Take the scale as the average of our triangles
    floating_point_t sum = 0;
    for (const auto& triangle : _triangles)
        sum += triangle.get_scale();
    sum /= _triangles.size();
    
    return sum;
}
    
void polygon::rotate(floating_point_t a, floating_point_t b, floating_point_t c)
{
    for (auto& triangle : _triangles)
        triangle.rotate(a, b, c);
}

void polygon::set_material(const fundamental_object::material& mat)
{
    _mat = mat;
    for (auto& i : _triangles)
        i.mat = mat;
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
    v.set_material(v._mat);

    return is;
}

std::ostream& operator<<(std::ostream& os, const polygon& v)
{
    return os;
}