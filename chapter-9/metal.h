#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "ray.h"
#include "vec3.h"

class metal: public material{
    public:
        metal(const vec3& a) : albedo(a){}

        virtual bool scatter(const ray& r, const hit_record& rec, vec3& atttenuation, ray& scattered) const{
            vec3 reflected = relect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, relected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0)
        }
        vec3 albedo;
}

#endif