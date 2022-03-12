#pragma once

#include "parallelogram.h"

class parallelepiped: public object
{
public:
	parallelepiped(const spacial_t& x, const spacial_t& y, const spacial_t& z);

	std::optional<colour_t> get_colour(const ray_t& ray) const override;

	void set_centre(const spacial_t& centre) override;

private:
	typedef std::array<parallelogram, 6> parallelograms_t;
	parallelograms_t _parallelograms;
};