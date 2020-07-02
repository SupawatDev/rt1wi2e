#include <iostream>

#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
// float hit_sphere(const vec3&center, float radius, const ray&r){
//     vec3 oc = r.origin() - center;
//     float a = dot(r.direction(), r.direction());
//     float b = 2.0* dot(oc, r.direction());
//     float c = dot(oc, oc) - radius*radius;
//     float discriminant = b*b - 4*a*c;
//     if (discriminant < 0){
//         return -1.0;
//     }else{
//         return (-b-sqrt(discriminant))/(2.0*a);
//     }
// }

// vec3 color(const ray& r) {
//     vec3 sphere_pos = vec3(0,0,-1);
    
//     // First Sphere Detection
//     float t = hit_sphere(vec3(0,0,-1), 0.5, r);
//      if(t > 0.0f){ // if hit the sphere
//          vec3 normal = unit_vector(r.point_at_parameter(t)-vec3(0,0,-1)); //normal vector
//          return 0.5*vec3(normal.x()+3.f, normal.x()+1.3f, normal.z()+1);        
//      }

//     // Print background
//     vec3 unit_direction = unit_vector(r.direction());
//     t = 0.5*(unit_direction.y() + 1.0);
//     return (1.0-t)*vec3(1, 1, 1) + t*vec3(0.0, 0.7, 0.0);
// }

vec3 color(const ray& r, hitable * world){
    hit_record rec;
    if(world->hit(r, 0.0, FLT_MAX , rec)){
       return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) * t*vec3(0.3, 0.5, 0.9);
}

int main(){
    int n_width = 400;
    int n_height = 200;
    std::cout << "P3\n" << n_width << " " << n_height << "\n255\n";
    vec3 left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hitable *object_list[3];
    object_list[0] = new sphere(vec3(0,0,-1), 0.6);
    object_list[1] = new sphere(vec3(3,0,-4), 1);
    object_list[2] = new sphere(vec3(-3,0,-4), 1);
    hitable * world = new hitable_list(object_list, 3);

    for(int j = n_height-1; j >= 0; --j)
        for(int i = 0; i < n_width ; ++i){
            float u = float(i)/float(n_width);
            float v = float(j)/float(n_height);

            ray r(origin, left_corner + u*horizontal + v*vertical);
            vec3 col = color(r, world);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }

    return 0;
}


