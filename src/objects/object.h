#pragma once

#include "config.h"

#include <optional>

class object
{
public:
	virtual ~object() = default;

	struct hit_info
	{
		hit_info() = default;
		hit_info(colour_t col_, floating_point_t z_) : colour(col_), z(z_) { }
                
		colour_t colour;
		floating_point_t z;
		floating_point_t albedo;
                ray_t next_ray;
	};

	virtual std::optional<hit_info> get_hit_info(const ray_t& ray) const = 0;

	virtual void set_centre(const spacial_t& centre) { _centre = centre; }
	const spacial_t& get_centre() const { return _centre; }

protected:
	spacial_t _centre{ 0, 0, 0 };
};