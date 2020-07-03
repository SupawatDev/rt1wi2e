#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
class material
{
public:
    virtual bool scatter(const ray &r_in, const hit_record &r, vec3 &attenuation, ray &scattered) const = 0;
};
#endif