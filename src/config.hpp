#pragma once

#include "utils/line.hpp"
#include "utils/utils.hpp"

#include <random>
#include <filesystem>
#include <cstdint>

typedef uint16_t rgb_t;
typedef double floating_point_t;

constexpr rgb_t RGB_MAX = unstd::unsigned_max<rgb_t>();

#if 0
constexpr size_t IMAGE_WIDTH = 30720;
constexpr size_t IMAGE_HEIGHT = 17260;
#elif 0
constexpr size_t IMAGE_WIDTH = 15360;
constexpr size_t IMAGE_HEIGHT = 8630;
#elif 0
constexpr size_t IMAGE_WIDTH = 7680;
constexpr size_t IMAGE_HEIGHT = 4320;
#elif 0
constexpr size_t IMAGE_WIDTH = 3840;
constexpr size_t IMAGE_HEIGHT = 2160;
#elif 1
constexpr size_t IMAGE_WIDTH = 1920;
constexpr size_t IMAGE_HEIGHT = 1080;
#elif 1
constexpr size_t IMAGE_WIDTH = 640;
constexpr size_t IMAGE_HEIGHT = 480;
#else 
constexpr size_t IMAGE_WIDTH = 192;
constexpr size_t IMAGE_HEIGHT = 108;
#endif
constexpr floating_point_t ASPECT_RATIO = floating_point_t(IMAGE_WIDTH) / floating_point_t(IMAGE_HEIGHT);

typedef unstd::line<floating_point_t, 3> ray_t;

typedef unstd::vector<rgb_t, 3> colour_t;
typedef unstd::vector<floating_point_t, 3> spacial_t;
typedef unstd::matrix<floating_point_t, 3, 3> transform_t;

typedef std::array<colour_t, IMAGE_WIDTH*IMAGE_HEIGHT> image_t;
inline colour_t random_colour() { return RGB_MAX*colour_t({ rgb_t(rand() % 2), rgb_t(rand() % 2), rgb_t(rand() & 2) }); }

constexpr floating_point_t EPSILON = 1e-8;

constexpr floating_point_t DEPTH_THRESHOLD = 0.01;

constexpr size_t MSAA = 4;

spacial_t random_spacial(floating_point_t r);

constexpr colour_t BLACK = RGB_MAX*colour_t({ 0, 0, 0 });
constexpr colour_t RED   = RGB_MAX*colour_t({ 1, 0, 0 });
constexpr colour_t GREEN = RGB_MAX*colour_t({ 0, 1, 0 });
constexpr colour_t BLUE  = RGB_MAX*colour_t({ 0, 0, 1 });
constexpr colour_t WHITE = RGB_MAX*colour_t({ 1, 1, 1 });
constexpr colour_t GREY  = WHITE*0.5;

constexpr colour_t BACKGROUND_COLOUR = BLACK;

static const std::filesystem::path ROOT_PATH = "../../../../../";
static const std::filesystem::path OBJECTS_PATH = ROOT_PATH / "objects";
static const std::filesystem::path RENDERS_PATH = ROOT_PATH / "renders";

// Writes an image to ostream in PPM format
std::ostream& operator << (std::ostream& os, const image_t& image);
