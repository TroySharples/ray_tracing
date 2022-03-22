#include "objects/complex_polygon.hpp"
#include "objects/sphere.hpp"

#include "rendering/camera.hpp"
#include "rendering/render.hpp"

#include "utils/timer.hpp"

#include <memory>
#include <fstream>

using namespace rendering;

typedef std::vector<std::unique_ptr<object>> objects_t;

static std::string make_output_name()
{
    // Our output PPM file is just the unix time for now
    return std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()) + ".ppm";
}

static bool load_objects(objects_t& objects)
{
    // Pushes back a background sphere
#if 1
    {
        std::unique_ptr<sphere> obj = std::make_unique<sphere>(5.0);
        obj->set_centre({ 0.0, 0.0, -70.0 });

        objects.emplace_back(std::move(obj));
    }
#endif
    
    // Pushes back another few spheres
#if 1
    {
        std::unique_ptr<sphere> obj = std::make_unique<sphere>(1.0);
        obj->set_centre({ 4.0, 2.0, -35.0 });

        objects.emplace_back(std::move(obj));
    }
    {
        std::unique_ptr<sphere> obj = std::make_unique<sphere>(0.25);
        obj->set_centre({ -1.0, -0.5, -20.0 });

        objects.emplace_back(std::move(obj));
    }
    {
        std::unique_ptr<sphere> obj = std::make_unique<sphere>(1.5);
        obj->set_centre({ -1.0, -2.0, -60.0 });

        objects.emplace_back(std::move(obj));
    }
#endif

    // Pushes back a cow
#if 1
    {
        std::unique_ptr<complex_polygon> obj = std::make_unique<complex_polygon>();

        std::fstream fs((OBJECTS_PATH / "cow.obj").c_str());
        if (!fs)
            return false;

        fs >> *obj;
        obj->set_centre({ -4.0, 0.0, -55.0 });

        objects.emplace_back(std::move(obj));
    }
#endif

    // Pushes back a teapot
#if 1
    {
        std::unique_ptr<complex_polygon> obj = std::make_unique<complex_polygon>();

        std::fstream fs((OBJECTS_PATH / "teapot.obj").c_str());
        if (!fs)
            return false;

        fs >> *obj;
        obj->set_centre({ 4.0, -3.0, -45.0 });

        objects.emplace_back(std::move(obj));
    }
#endif

    // Pushes back a face
#if 0
    {
        std::unique_ptr<complex_polygon> obj = std::make_unique<complex_polygon>();

        std::fstream fs((OBJECTS_PATH / "face.obj").c_str());
        if (!fs)
            return false;

        fs >> *obj;
        obj->set_centre({ 0.0, -0.0, -8.0 });

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
    camera cam;

    // Does the rendering
    render_msaa(objects, cam, img);

    // Outputs the rendered PPM
    std::ofstream of(RENDERS_PATH / make_output_name());
    of << img;

    return 0;
}
