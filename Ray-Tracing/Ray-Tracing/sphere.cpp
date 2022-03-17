#include "sphere.h"

sphere::sphere(floating_point_t radius_)
	: radius(radius_)
{

}

std::optional<object::hit_info> sphere::get_hit_info(const ray_t& ray) const
{
	const spacial_t oc = ray.origin - _centre;
	const floating_point_t a = ray.direction.square_length();
	const floating_point_t b = floating_point_t(2.0)*unstd::dot_product(oc, ray.direction);
	const floating_point_t c = oc.square_length() - radius*radius;
	
	return (b * b - 4 * a * c > 0) ? hit_info(RED, oc.length() - radius) : std::optional<hit_info>();
}