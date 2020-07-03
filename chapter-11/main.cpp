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
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted){
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant>0){
        refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
        return true;
    }else{
        return false;
    }
}
vec3 reflect(const vec3& v, const vec3& n){
    return v-2*dot(v,n)*n;
}

float schlick(float cosine, float ref_idx){
    float r0 = (1-ref_idx)/(1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow(1 - cosine,5);
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

class dielectric: public material{
    public:
        dielectric(float ri) : ref_index(ri){}
        virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const{
            vec3 outward_normal;
            vec3 reflected = reflect(r.direction(), rec.normal);
            float ni_over_nt;
            attenuation = vec3(1., 1., 1.);
            vec3 refracted;
            float reflect_prob;
            float cosine;
            if (dot(r.direction(), rec.normal) > 0){
                    outward_normal = -rec.normal;
                    ni_over_nt = ref_index;
                    cosine = ref_index*dot(r.direction(), rec.normal) / r.direction().length();
            }else{
                    outward_normal = rec.normal;
                    ni_over_nt = 1.0 /ref_index;
                    cosine = -dot(r.direction(), rec.normal)/r.direction().length();
            }

            if(refract(r.direction(), outward_normal, ni_over_nt, refracted)){
                reflect_prob =  schlick(cosine, ref_index);
            }else{
                scattered = ray(rec.p, reflected);
                reflect_prob = 1.0;
            }

            if(drand48() < reflect_prob){
                scattered = ray(rec.p, reflected);
            }else{
                scattered = ray(rec.p, refracted);
            }

            return true;
        }
        float ref_index;
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
    int n_sample = 10;
    srand(time(NULL));
    std::cout << "P3\n"
              << n_width << " " << n_height << "\n255\n";

    hitable *object_list[5];
    object_list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 2, 0.5)));
    object_list[1] = new sphere(vec3(1, -100.5, -1), 100, new lambertian(vec3(0.2, 0.2, 0.9)));
    object_list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.3, 0.4, 0.3), 0));
    object_list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    object_list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
    hitable *world = new hitable_list(object_list, 5);

    vec3 lookfrom(3,3,2);
    vec3 lookat(0,0,-1);
    float aperture = 3;
    float dist_to_focus = (lookfrom - lookat).length();

    camera cam(lookfrom, lookat, vec3(0, 1,0), 20, float(n_width)/float(n_height), aperture, dist_to_focus);
    for (int j = n_height - 1; j >= 0; --j)
        for (int i = 0; i < n_width; ++i)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < n_sample; ++s)
            {
                float u = float(i + drand48()) / float(n_width);
                float v = float(j + drand48()) / float(n_height);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
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
