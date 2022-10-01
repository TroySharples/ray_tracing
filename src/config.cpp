#include "config.hpp"

#include "utils/utils.hpp"

#include <random>

spacial_t random_spacial(floating_point_t r)
{
    static thread_local std::mt19937 generator(std::random_device{ }());
    std::uniform_real_distribution<floating_point_t> unif(0, std::sqrt(1.0/3.0));
    
    spacial_t ret;
    for (auto& i : ret)
        i = r*unif(generator);
    
    return ret;
}

std::ostream& operator << (std::ostream& os, const image_t& image)
{
    // The header
    os << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n" << (int)unstd::unsigned_max<colour_t::value_type>() << "\n";
    
    // Print starting with the top left pixel
    for (const colour_t& i : image) 
        os << i;
    os << "\n";

    return os;
}