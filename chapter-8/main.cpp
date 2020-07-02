#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"
#include "material.h"

vec3 random_in_unit_sphere()
{
    vec3 p;
    //p = 1.5*vec3(drand(), drand(), drand()) - vec3(1,1,1);
    do
    {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

class lambertian : public material
{
public:
    lambertian(const vec3 &a) : albedo(a) {}

    virtual bool scatter(const ray &r, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
    vec3 albedo;
};

class metal : public material
{
public:
    metal(const vec3 &a ,float f ) : albedo(a) {if(f<1)fuzz = f; else fuzz =1;}

    virtual bool scatter(const ray &r, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 reflected = reflect(unit_vector(r.direction()), rec.normal);
        scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    vec3 albedo;
    float fuzz;
};

vec3 color(const ray &r, hitable *world, int depth)
{
    hit_record rec;
    if (world->hit(r, 0.0001, FLT_MAX, rec))
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.4, 0.4, 1);
}

int main()
{
    int n_width = 800;
    int n_height = 400;
    int n_sample = 20;
    srand(time(NULL));
    std::cout << "P3\n"
              << n_width << " " << n_height << "\n255\n";

    hitable *object_list[4];
    object_list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.9, 1, 0.3)));
    object_list[1] = new sphere(vec3(1.5, -.2, -1), 0.5, new metal(vec3(1, 1, 1), 0.4));
    object_list[2] = new sphere(vec3(-1.5, -.2, -1), 0.5, new metal(vec3(0.3, 0.4, 0.3), 0));
    object_list[3] = new sphere(vec3(0, -100.5, -5), 100, new lambertian(vec3(1, 0.6, 1)));
    hitable *world = new hitable_list(object_list, 4);
    camera cam;
    for (int j = n_height - 1; j >= 0; --j)
        for (int i = 0; i < n_width; ++i)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < n_sample; ++s)
            {
                float u = float(i + drand48()) / float(n_width);
                float v = float(j + drand48()) / float(n_height);
                ray r = cam.get_ray(u, v);
                //vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 20);
            }
            col /= float(n_sample);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }

    return 0;
}
