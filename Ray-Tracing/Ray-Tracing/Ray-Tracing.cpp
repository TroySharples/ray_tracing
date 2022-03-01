#include <iostream>
#include <cstdint>
#include <array>
#include <fstream>
#include "Vector3.h"

// Image
static constexpr size_t IMAGE_WIDTH = 2560;
static constexpr size_t IMAGE_HEIGHT = 1440;

template <typename _T>
static size_t unsigned_max() { return std::pow(2, 8 * sizeof(_T)) - 1; }

typedef uint16_t colour_t;
typedef unstd::Vector3<colour_t> pixel_t;
typedef std::array<pixel_t, IMAGE_WIDTH * IMAGE_HEIGHT> image_t;
std::ostream& operator << (std::ostream& os, const image_t& image) 
{  
	os << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n" << unsigned_max<colour_t>() << "\n";

	for (const pixel_t& i : image) { os << i << " "; }

	os << "\n";

	return os;
}

void foo(int a, int b, int c);

static image_t image;

int main()
{
	 //Render
	 //For each pixel I need an RGB value
	 //Each pixel will be an RGB triplet

	for (size_t h = 0; h < IMAGE_HEIGHT; h++)
	{
		for (size_t w = 0; w < IMAGE_WIDTH; w++)
		{
			pixel_t& pixel = image[IMAGE_WIDTH * h + w];
			pixel.e[0] = h * unsigned_max<colour_t>() / IMAGE_HEIGHT;
			pixel.e[1] = w * unsigned_max<colour_t>() / IMAGE_WIDTH;
			pixel.e[2] = 0.25 * unsigned_max<colour_t>();
		}
	}

	std::ofstream of("Render_Output.ppm");
	of << image;

	return 0;
}

void foo(int a, int b, int c)
{
}
