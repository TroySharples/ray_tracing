#include "objects/polygon.h"
#include "objects/sphere.h"

#include "rendering/camera.h"
#include "rendering/renderer.h"

#include "utils/timer.h"

#include <memory>
#include <fstream>

typedef std::vector<std::unique_ptr<object>> objects_t;

static std::string make_output_name()
{
    // Our output PPM file is just the unix time for now
    return std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()) + ".ppm";
}

static bool load_objects(objects_t& objects)
{
    // Pushes back a sphere
#if 0
    {
            std::unique_ptr<sphere> obj = std::make_unique<sphere>(2.5);
            obj->set_centre({ 0.0, 0.0, -55.0 });

            objects.emplace_back(std::move(obj));
    }
#endif

    // Pushes back a cow
#if 1
    {
            std::unique_ptr<polygon> obj = std::make_unique<polygon>();

            std::fstream fs((OBJECTS_PATH / "cow.obj").c_str());
            if (!fs)
                    return false;

            fs >> *obj;
            obj->set_centre({ -1.0, 0.0, -75.0 });

            objects.emplace_back(std::move(obj));
    }
#endif

    // Pushes back a teapot
#if 1
    {
            std::unique_ptr<polygon> obj = std::make_unique<polygon>();

            std::fstream fs((OBJECTS_PATH / "teapot.obj").c_str());
            if (!fs)
                    return false;

            fs >> *obj;
            obj->set_centre({ 1.0, -3.0, -65.0 });

            objects.emplace_back(std::move(obj));
    }
#endif

    return true;
}

int main()
{
	// Creates an objects vector and loads it up
	objects_t objects;
	if (!load_objects(objects))
		return 1;

	// Too big to be allocated on the stack
	static image_t img;

	// Camera 
	camera cam1;

	// Does the rendering
	renderer r;
	r.render(objects, img, cam1);

	// Outputs the rendered PPM
	std::ofstream of(RENDERS_PATH / make_output_name());
	of << img;

	return 0;
}