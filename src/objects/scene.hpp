#pragma once

#include "parallelepiped.hpp"

class scene : public object
{
public:
    std::optional<hit_info> get_hit_info(const ray_t& ray) const override;
    
    boundary get_boundary() const override;

    void set_centre(spacial_t centre) override;
    
    void set_scale(floating_point_t scale) override;
    floating_point_t get_scale() const override;
    
    void rotate(floating_point_t a, floating_point_t b, floating_point_t c) override;
    
    typedef std::vector<std::unique_ptr<object>> objects_t;
    
    void push_object(std::unique_ptr<object> object);
    void fragment();

private:
    objects_t _objects;
    
    mutable std::optional<parallelepiped> _bounding_box;

private:
    void make_bounding_box() const;
};