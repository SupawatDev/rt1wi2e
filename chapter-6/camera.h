#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
public:
    camera(){
        left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }

    ray get_ray(float u, float v){return ray(origin, left_corner + horizontal*u + vertical*v - origin );}

    vec3 left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
};

#endif