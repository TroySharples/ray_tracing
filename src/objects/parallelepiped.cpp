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
    {
        const auto info = i.get_hit_info(ray);
        if (info.has_value() && (!ret.has_value() || ret.value().z2 > info.value().z2))
            ret = info;
    }

    return ret;
}

void parallelepiped::set_centre(const spacial_t& centre)
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