#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray{
public:
    ray(){};
    ray(const vec3& position, const vec3 direction){ p = position; d = direction; }
    vec3 origin() const {return p;}
    vec3 direction() const {return d;}
    vec3 point_at_parameter(float t) const {return p+t*d;}
    
    vec3 p;
    vec3 d;
};
#endif


