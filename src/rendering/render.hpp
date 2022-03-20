#pragma once

#include "rendering/camera.hpp"
#include "config.hpp"

#include <memory>

class object;

namespace rendering
{
    typedef std::vector<std::unique_ptr<object>> objects_t;

    void render(const objects_t& objects, const camera& cam, image_t& img);
    void render_msaa(const objects_t& objects, const camera& cam, image_t& img);
}