#include<iostream>
#include "ray.h"

vec3 color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1, 1, 1) + t*vec3(0.0, 0.7, 0.0);
}

int main(){
    int n_width = 200;
    int n_height = 100;
    std::cout << "P3\n" << n_width << " " << n_height << "\n255\n";
    vec3 left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for(int j = n_height-1; j >= 0; --j)
        for(int i = 0; i < n_width ; ++i){
            float u = float(i)/float(n_width);
            float v = float(j)/float(n_height);

            ray r(origin, left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            //col.make_unit_vector();
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }

    return 0;
}


