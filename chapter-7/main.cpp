#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"

float drand(){
    return float(rand()%2 - 1.001f);
}
vec3 random_in_unit_sphere(){
    vec3 p;
    //p = 1.5*vec3(drand(), drand(), drand()) - vec3(1,1,1);
    do {
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
    }
    while (p.squared_length() >= 1.0);
    return p;
}

vec3 color(const ray& r, hitable * world){
    hit_record rec;
    if(world->hit(r, 0.0001, FLT_MAX , rec)){
       vec3 target = rec.p + rec.normal + random_in_unit_sphere();
       return 0.5*color(ray(rec.p, target-rec.p), world);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.7, 0.8, 1);
}

int main(){
    int n_width = 400;
    int n_height = 200;
    int n_sample = 20;
    srand(time(NULL));
    std::cout << "P3\n" << n_width << " " << n_height << "\n255\n";

    hitable *object_list[4];
    object_list[0] = new sphere(vec3(0,0,-1), 0.5);
    object_list[1] = new sphere(vec3(1.5,-.2,-2), 0.25);
    object_list[2] = new sphere(vec3(-1.5,-.2,-2), 0.25);
    object_list[3] = new sphere(vec3(0,-100.5,-5), 100);
    hitable * world = new hitable_list(object_list, 4);
    camera cam;
    for(int j = n_height-1; j >= 0; --j)
        for(int i = 0; i < n_width ; ++i){
            vec3 col(0,0,0);
            for(int s = 0; s < n_sample; ++s){
                float u = float(i+drand48())/float(n_width);
                float v = float(j+drand48())/float(n_height);
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(n_sample);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }

    return 0;
}


