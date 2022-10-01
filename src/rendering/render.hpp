#pragma once

#include "rendering/camera.hpp"
#include "config.hpp"

#include <memory>

class object;

namespace rendering
{
    void render(const object& obj, const camera& cam, image_t& img);
    void render_msaa(const object& obj, const camera& cam, image_t& img);
}