#include <iostream>
#include <cstdlib>
#include <time.h>

#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"

vec3 color(const ray& r, hitable * world){
    hit_record rec;
    if(world->hit(r, 0.0, FLT_MAX , rec)){
       return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) * t*vec3(0.4, 0.5, 0.5);
}

int main(){
    int n_width = 400;
    int n_height = 200;
    int n_sample = 1000;
    srand(0);
    std::cout << "P3\n" << n_width << " " << n_height << "\n255\n";

    hitable *object_list[3];
    object_list[0] = new sphere(vec3(0,0,-1), 0.6);
    object_list[1] = new sphere(vec3(3,0,-4), 1);
    object_list[2] = new sphere(vec3(-3,0,-4), 1);
    hitable * world = new hitable_list(object_list, 3);
    camera cam;
    for(int j = n_height-1; j >= 0; --j)
        for(int i = 0; i < n_width ; ++i){
            vec3 col(0,0,0);
            for(int s = 0; s < n_sample; ++s){
                float ur = float(rand()%2 - 1.000001f);
                float uv = float(rand()%2 - 1.000001f);
                float u = float(i+ur)/float(n_width);
                float v = float(j+uv)/float(n_height);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);
            }
            col /= float(n_sample);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }

    return 0;
}


