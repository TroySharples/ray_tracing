#pragma once

#include "rendering/camera.h"
#include "utils/timer.h"

#include "config.h"

#include <memory>

class object;

typedef std::vector<std::unique_ptr<object>> objects_t;

class renderer
{
public:
	renderer() = default;
	~renderer() = default;
	static void render(const objects_t& objects, image_t& img, const camera cam);

private:

};