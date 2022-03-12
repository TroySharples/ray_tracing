#pragma once

#include "object.h"

class sphere : public object
{
public:
	sphere(floating_point_t radius_);

	std::optional<colour_t> get_colour(const ray_t& ray) const override;
	
	const floating_point_t radius;
};