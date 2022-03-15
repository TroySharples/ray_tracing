#pragma once

#include "line.h"
#include "utils.h"

#include <random>
#include <cstdint>

typedef uint8_t rgb_t;
typedef double floating_point_t;

constexpr rgb_t RGB_MAX = unstd::unsigned_max<rgb_t>();

// Image.
constexpr size_t IMAGE_WIDTH = 640;
constexpr size_t IMAGE_HEIGHT = 360;
constexpr floating_point_t ASPECT_RATIO = floating_point_t(IMAGE_WIDTH) / floating_point_t(IMAGE_HEIGHT);

typedef unstd::line<floating_point_t, 3> ray_t;

typedef unstd::vector<rgb_t, 3> colour_t;
typedef unstd::vector<floating_point_t, 3> spacial_t;
typedef unstd::vector<floating_point_t, 2> texord_t;

typedef std::array<colour_t, IMAGE_WIDTH*IMAGE_HEIGHT> image_t;
inline colour_t random_colour() { return colour_t({ rgb_t(rand()), rgb_t(rand()), rgb_t(rand()) }); }

constexpr colour_t RED = RGB_MAX * colour_t({ 1, 0, 1 });
constexpr colour_t BLUE = RGB_MAX * colour_t({ 0, 1, 0 });
constexpr colour_t WHITE = RGB_MAX * colour_t({ 1, 1, 1 });

// Writes an image to ostream in PPM format
std::ostream& operator << (std::ostream& os, const image_t& image);

struct virtex
{
	spacial_t position;
	colour_t  colour;
	texord_t  texcoord;
	spacial_t normal;
};