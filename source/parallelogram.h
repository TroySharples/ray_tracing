#pragma once

#include "object.h"

#include <optional>

class parallelogram : public object
{
public:
	typedef spacial_t vertex_t;
	typedef std::array<vertex_t, 3> vertices_t;

	parallelogram() = default;
	parallelogram(const vertices_t& vertices);

	std::optional<colour_t> get_colour(const ray_t& ray) const override;

	vertex_t& operator[](size_t i);
	const vertex_t& operator[](size_t i) const;

private:
	vertices_t _vertices;
	mutable std::optional<spacial_t> _normal;
};
