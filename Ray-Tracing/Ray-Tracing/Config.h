#pragma once
#include "Vector3.h"
#include "Utils.h"
#include <array>

// Image.
constexpr float ASPECT_RATIO = 16.0 / 9.0;
constexpr size_t IMAGE_WIDTH = 200;
constexpr size_t IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;

typedef uint16_t colour_t;
typedef unstd::Vector3<colour_t> pixel_t;
typedef std::array<pixel_t, IMAGE_WIDTH* IMAGE_HEIGHT> image_t;

std::ostream& operator << (std::ostream& os, const image_t& image)
{
	os << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n" << unstd::unsigned_max<colour_t>() << "\n";

	for (const pixel_t& i : image) { os << i << " "; }

	os << "\n";

	return os;
}