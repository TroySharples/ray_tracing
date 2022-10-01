#include "parallelepiped.hpp"

parallelepiped::parallelepiped(const spacial_t& x, const spacial_t& y, const spacial_t& z)
{
    _parallelograms[0] = parallelogram({ _centre, _centre + x, _centre + y });
    _parallelograms[1] = parallelogram({ _centre, _centre + y, _centre + z });
    _parallelograms[2] = parallelogram({ _centre, _centre + z, _centre + x });
    _parallelograms[3] = parallelogram({ _centre + x + y + z, _centre + y + z, _centre + x + z });
    _parallelograms[4] = parallelogram({ _centre + x + y + z, _centre + x + z, _centre + x + y });
    _parallelograms[5] = parallelogram({ _centre + x + y + z, _centre + x + y, _centre + y + z });
}

std::optional<object::hit_info> parallelepiped::get_hit_info(const ray_t& ray) const
{
    std::optional<hit_info> ret;
    for (const auto& i : _parallelograms)
        if (const auto info = i.get_hit_info(ray); info.has_value() && (!ret.has_value() || ret.value().z2 > info.value().z2))
            ret = info;

    return ret;
}

parallelepiped::boundary parallelepiped::get_boundary() const
{
    boundary ret = _parallelograms[0].get_boundary();
    for (const auto& parallelogram : _parallelograms)
    {
        boundary b = parallelogram.get_boundary();
        for (size_t i = 0; i < 3; i++)
        {
            ret.min[i] = std::min(ret.min[i], b.min[i]); 
            ret.max[i] = std::max(ret.max[i], b.max[i]); 
        }
    }
    
    return ret;
}

void parallelepiped::set_centre(spacial_t centre)
{
    // Also reset centre for each of our parallelograms as well
    _centre = centre;
    for (auto& i : _parallelograms)
        i.set_centre(_centre);
}

floating_point_t parallelepiped::get_volume() const
{
    return unstd::scalar_triple_product(_parallelograms[0][1] - _parallelograms[0][0], _parallelograms[1][1] - _parallelograms[1][0], _parallelograms[2][1] - _parallelograms[2][0]);
}

spacial_t parallelepiped::get_centre() const
{
    // Just returns the point between thew two opposite vertices
    return (_parallelograms[0][0] + _parallelograms[3][1] + _parallelograms[3][2]) / floating_point_t(2);
}

void parallelepiped::set_scale(floating_point_t scale)
{
    const floating_point_t factor = scale / get_scale();
    for (auto& parallelogram : _parallelograms)
        parallelogram.enlarge(factor);;
}

floating_point_t parallelepiped::get_scale() const
{
    return std::cbrt(get_volume());
}
    
void parallelepiped::rotate(floating_point_t a, floating_point_t b, floating_point_t c)
{
    for (auto& parallelogram : _parallelograms)
        parallelogram.rotate(a, b, c);
}