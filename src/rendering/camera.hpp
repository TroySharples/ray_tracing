#pragma once

#include "config.hpp"

struct camera
{
    camera() = default;
    camera(spacial_t origin_, spacial_t horizontal_, spacial_t vertical_)
        : origin(origin_), horizontal(horizontal_), vertical(vertical_) { }

    spacial_t origin = { 0, 0, 0 };
    spacial_t horizontal = { cam_width, 0, 0 };
    spacial_t vertical = { 0 , cam_height, 0 };
    spacial_t lower_left_corner = origin - horizontal / floating_point_t(2.0) - vertical / floating_point_t(2.0) - spacial_t({ 0, 0, focal_length });

    static constexpr floating_point_t cam_height = floating_point_t(2.0);
    static constexpr floating_point_t cam_width = ASPECT_RATIO * cam_height;
    static constexpr floating_point_t focal_length = floating_point_t(10.0);
};