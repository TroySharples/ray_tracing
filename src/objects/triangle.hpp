#pragma once

#include "object.hpp"

class triangle : public object
{
public:
	typedef spacial_t vertex_t;
	typedef std::array<vertex_t, 3> vertices_t;

	triangle() = default;
	triangle(const vertices_t& vertices);

	std::optional<hit_info> get_hit_info(const ray_t& ray) const override;

	vertex_t& operator[](size_t i);
	const vertex_t& operator[](size_t i) const;

	vertices_t::const_iterator begin() const { return _vertices.begin(); }
	vertices_t::const_iterator end() const { return _vertices.end(); }

private:
	vertices_t _vertices;
	colour_t _colour = random_colour();

	mutable std::optional<spacial_t> _normal;

private:
	void make_normal() const;
};

