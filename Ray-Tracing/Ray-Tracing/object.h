#pragma once

#include "config.h"

#include <optional>

class object
{
public:
	virtual ~object() = default;

	virtual std::optional<colour_t> get_colour(const ray_t& ray) const = 0;

	virtual void set_centre(const spacial_t& centre) { _centre = centre; }
	const spacial_t& get_centre() const { return _centre; }

protected:
	spacial_t _centre{ 0, 0, 0 };
};