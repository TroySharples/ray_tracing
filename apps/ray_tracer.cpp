#include "objects/scene.hpp"
#include "objects/polygon.hpp"
#include "objects/fundamental/sphere.hpp"

#include "rendering/camera.hpp"
#include "rendering/render.hpp"

#include <memory>
#include <fstream>

using namespace rendering;

static std::string make_output_name()
{
    // Our output PPM file is just the unix time for now
    return std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

static void push_polygon(const polygon& poly, scene& s)
{
    auto& triangles = poly.get_triangles();
    
    for (auto& obj : triangles)
        s.push_object(std::make_unique<triangle>(obj));
}

static bool load_objects(scene& s)
{
    // Pushes back a background sphere
#if 1
    {
        std::unique_ptr<sphere> obj = std::make_unique<sphere>();
        obj->set_scale(5.0);
        obj->set_centre({ 0.0, 0.0, -70.0 });

        s.push_object(std::move(obj));
    }
#endif
    
    // Pushes back another few spheres
#if 1
    {
        std::unique_ptr<sphere> obj = std::make_unique<sphere>();
        obj->set_scale(1.0);
        obj->set_centre({ 4.0, 2.0, -35.0 });

        s.push_object(std::move(obj));
    }
    {
        std::unique_ptr<sphere> obj = std::make_unique<sphere>();
        obj->set_scale(0.25);
        obj->set_centre({ -1.0, -0.5, -20.0 });

        s.push_object(std::move(obj));
    }
    {
        std::unique_ptr<sphere> obj = std::make_unique<sphere>();
        obj->set_scale(1.5);
        obj->set_centre({ -1.0, -2.0, -60.0 });

        s.push_object(std::move(obj));
    }
#endif

    // Pushes back a cow
#if 0
    {
        std::unique_ptr<polygon> obj = std::make_unique<polygon>();

        std::fstream fs((OBJECTS_PATH / "cow.obj").c_str());
        if (!fs)
            return false;

        fs >> *obj;
        obj->enlarge(0.5);
        obj->rotate(0, 3*M_PI/2, 0);
        obj->set_centre({ -4.0, 3.0, -55.0 });

        push_polygon(*obj, s);
    }
#endif

    // Pushes back a teapot
#if 0
    {
        std::unique_ptr<polygon> obj = std::make_unique<polygon>();

        std::fstream fs((OBJECTS_PATH / "teapot.obj").c_str());
        if (!fs)
            return false;

        fs >> *obj;
        obj->enlarge(1.5);
        obj->rotate(0, 0, M_PI);
        obj->set_centre({ 4.0, 2.0, -45.0 });

        push_polygon(*obj, s);
    }
#endif

    // Pushes back a face
#if 0
    {
        std::unique_ptr<polygon> obj = std::make_unique<polygon>();

        std::fstream fs((OBJECTS_PATH / "face.obj").c_str());
        if (!fs)
            return false;

        fs >> *obj;
        obj->set_centre({ 0.0, -0.0, -8.0 });

        push_polygon(*obj, s);
    }
#endif
    
    s.fragment();

    return true;
}

int main()
{
    // Creates an scene and loads it up
    scene s;
    if (!load_objects(s))
            return 1;

    // Too big to be allocated on the stack
    static image_t img;
    camera cam;

    // Does the rendering
    render_msaa(s, cam, img);

    // Creates the output name
    const auto output_name = make_output_name();

    // Outputs the rendered PPM
    {
        std::ofstream os(output_name + ".ppm");
        os << img;
    }
    
    // Hacky convert any PPMs to PNGs. A much nicer way of doing this would be to use libpng
    std::system("find -name \'*.ppm\' -exec bash -c \'convert \"$0\" \"${0/ppm/png}\"\' {} \\;; rm *ppm");

    // Output the PPM file to stdout
    {
        std::ifstream is(output_name + ".png");
        std::cout << is.rdbuf();
    }
    std::remove((output_name + ".png").c_str());

    return 0;
}
