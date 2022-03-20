#include "config.hpp"

#include "utils/utils.hpp"

spacial_t random_spacial(floating_point_t r)
{
    spacial_t ret;
    for (auto& i : ret)
        i = r*floating_point_t(rand())/RAND_MAX;
    
    return ret;
}

std::ostream& operator << (std::ostream& os, const image_t& image)
{
    os << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n" << (int)unstd::unsigned_max<colour_t::value_type>() << "\n";
    for (const colour_t& i : image) { os << i; }
    os << "\n";

    return os;
}