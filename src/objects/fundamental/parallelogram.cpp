#include "parallelogram.hpp"

parallelogram::parallelogram(const vertices_t& vertices)
    : _vertices(vertices)
{

}

std::optional<object::hit_info> parallelogram::get_hit_info(const ray_t& ray) const
{
    std::optional<hit_info> ret;
    
    // The absolute position of the parallelogram
    const vertices_t absolute = { _vertices[0] + _centre, _vertices[1] + _centre, _vertices[2] + _centre };

    // Compute the normal of the plane the parallelogram is in (the cross product of two of its sides)
    const spacial_t side0 = absolute[0] - absolute[2];
    const spacial_t side1 = absolute[1] - absolute[0];

    // Calculate the normal if necessary
    if (!_normal.has_value()) { make_normal(); }
    const spacial_t& normal = _normal.value();

    // Compute how aligned the normal to the parallelogram and the direction of the ray are (their dot product)
    const floating_point_t alignment = -unstd::dot_product(normal, ray.direction);

    // The ray will never hit if its direction is orthoganal to the normal of the parallelogram
    if (std::abs(alignment) < EPSILON) return ret;

    // Compute the distance along the ray which intersects with the plane
    const floating_point_t t = unstd::dot_product(normal, ray.origin - absolute[0]) / alignment;

    // If t is negative the parallelogram is behind the camera
    if (t < EPSILON) return ret;

    // Compute the actual point of interesection and the displacement vector to this point
    const spacial_t intersection = ray[t];

    // Are we right of the first side?
    if (unstd::scalar_triple_product(normal, side0, intersection - absolute[2]) < 0) return ret;

    // Are we right of the second side?
    if (unstd::scalar_triple_product(normal, side1, intersection - absolute[0]) < 0) return ret;

    // Are we right of the third side?
    if (unstd::scalar_triple_product(normal, side0, intersection - absolute[1]) > 0) return ret;

    // Are we right of the fourth side?
    if (unstd::scalar_triple_product(normal, side1, intersection - absolute[2]) > 0) return ret;

    // We hit the parallelogram if we made it here    
    ret = calculate_hit_info(intersection, ray.direction, normal, std::pow(t, 2), alignment);
    
    return ret;
}

parallelogram::vertex_t& parallelogram::operator[](size_t i)
{
    // We have to assume the vertices will be changed
    _normal.reset();
    return _vertices[i];
}

const parallelogram::vertex_t& parallelogram::operator[](size_t i) const
{
    return _vertices[i];
}

floating_point_t parallelogram::get_area() const
{
    return 0.5*unstd::cross_product(_vertices[0] - _vertices[2], _vertices[1] - _vertices[0]).length();
}

spacial_t parallelogram::get_centre() const
{
    // Just returns the point between thew two opposite vertices
    return (_vertices[0] + _vertices[2]) / floating_point_t(2);
}

void parallelogram::make_normal() const
{
    _normal = unstd::cross_product(_vertices[0] - _vertices[2], _vertices[1] - _vertices[0]);
    _normal.value().normalise();
}
