#include "scene.hpp"

#include <algorithm>

static std::vector<scene::objects_t> octant(scene::objects_t& objects)
{
    std::vector<scene::objects_t> ret;
    
    // Find the centre of all the objects
    spacial_t centre = { 0, 0, 0 };
    for (const auto& obj : objects)
        centre += obj->get_centre();
    centre /= objects.size();
    
    // Split the polygon into 8 Cartesian segments about the centre
    ret.resize(8);
    for (auto& obj : objects)
    {
        const auto& c = obj->get_centre();
        const size_t i = 0b001*(c[0] < centre[0] ? 1 : 0)
                + 0b010*(c[1] < centre[1] ? 1 : 0)
                + 0b100*(c[2] < centre[2] ? 1 : 0);
        ret[i].emplace_back(std::move(obj));
    }
    
    // Removes any segments that are empty
    std::erase_if(ret, [](const auto& i) { return i.empty() ; }); 
    
   return ret;
}

static std::vector<scene::objects_t> recursive_octant(scene::objects_t& objects, bool (*predicate)(const scene::objects_t&))
{
    std::vector<scene::objects_t> ret;
    
    // Recursively octants until the predicate it met
    if (predicate(objects))
    {
        ret.emplace_back(std::move(objects));
    }
    else
    {
        auto once = octant(objects);
        for (auto& i : once)
        {
            auto recurse = recursive_octant(i, predicate);
            ret.insert(ret.end(), std::make_move_iterator(recurse.begin()), std::make_move_iterator(recurse.end()));
        }
    }
    
   return ret;
}

static std::vector<scene::objects_t> fragment_objects(scene::objects_t& objects)
{
    // Can look into more predicates / fragmentation methods in the future
    constexpr size_t fragments = 10;
    return recursive_octant(objects, [](const auto& i) { return i.size() < fragments; });
}

std::optional<object::hit_info> scene::get_hit_info(const ray_t& ray) const
{
    std::optional<hit_info> ret;
    
    // Make our bounding box if we haven't already
    if (!_bounding_box.has_value())
        make_bounding_box();
    const auto& bounding_box = _bounding_box.value();

    // Return false straight away if we don't hit the bounding box
    if (!bounding_box.get_hit_info(ray).has_value())
        return ret;
    
    // Render the objects
    for (const auto& obj : _objects)
        if (const auto info = obj->get_hit_info(ray); info.has_value() && (!ret.has_value() || ret.value().z2 > info.value().z2))
            ret = info;
    
    return ret;
}

scene::boundary scene::get_boundary() const
{
    // Return if we contain no objects
    if (_objects.empty())
        return {};
      
    boundary ret = _objects[0]->get_boundary();
    for (const auto& obj:  _objects)
    {
        boundary b = obj->get_boundary();
        for (size_t i = 0; i < 3; i++)
        {
            ret.min[i] = std::min(ret.min[i], b.min[i]); 
            ret.max[i] = std::max(ret.max[i], b.max[i]); 
        }
    }
    
    return ret;
}

void scene::set_centre(spacial_t centre)
{
    _centre = centre;
    for (auto& obj : _objects)
        obj->set_centre(centre);
    
    _bounding_box.reset();
}

void scene::set_scale(floating_point_t scale)
{
    const floating_point_t factor = scale / get_scale();
    for (auto& obj : _objects)
        obj->enlarge(factor);
    
    _bounding_box.reset();
}

floating_point_t scene::get_scale() const
{
    // For now we just take the scale as the average of our owned objects. We should probably change this to the scale of our bounding box
    floating_point_t sum = 0;
    for (const auto& obj : _objects)
        sum += obj->get_scale();
    sum /= _objects.size();
    
    return sum;
}
    
void scene::rotate(floating_point_t a, floating_point_t b, floating_point_t c)
{
    for (auto& obj : _objects)
        obj->rotate(a, b, c);
    
    _bounding_box.reset();
}

void scene::push_object(std::unique_ptr<object> object)
{
    _objects.emplace_back(std::move(object));
}

void scene::fragment()
{
    std::vector<scene::objects_t> fragments = fragment_objects(_objects);
    for (auto& objects : fragments)
    {
        auto object = std::make_unique<scene>();
        object->_objects = std::move(objects);
        _objects.emplace_back(std::move(object));
    }
}

void scene::make_bounding_box() const
{
    // Find our own boundary
    boundary b = get_boundary();
    
    // Make the diagonal vector that spans the whole set of objects
    const spacial_t diagonal = b.max - b.min;

    // Make the x, y, z coordinates for the parallelepiped
    const spacial_t x = { diagonal[0], 0, 0 };
    const spacial_t y = { 0, diagonal[1], 0 };
    const spacial_t z = { 0, 0, diagonal[2] };

    // Make the parallelepiped with the centre set properly
    _bounding_box = parallelepiped(x, y, z);
    _bounding_box.value().set_centre(_centre + b.min);
}