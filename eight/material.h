#ifndef MATERIAL_H
#define MATERIAL_H

#include "hitable.h"  // or the appropriate header where hit_record is defined
#include"ray.h"

vec3 random_in_unit_sphere(); // forward declaration, or include the header where it's defined

struct hit_record;  // forward declaration of the hit_record struct

class material {
    public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;  // pure virtual function    

};

class lambertian: public material {
    public:
    lambertian(const vec3& a): albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();  // get a random point in the unit sphere
        scattered = ray(rec.p, target - rec.p);  // create a new ray
        attenuation = albedo;  // set the attenuation to the albedo
        return true;  // return true to indicate that the ray was scattered
    }
    vec3 albedo;  // color of the material
};

class metal: public material {
    public:
    metal(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);  
        scattered = ray(rec.p, reflected);
        attenuation = albedo;  // set the attenuation to the albedo
        return (dot(scattered.direction(), rec.normal) > 0);  
    }
    vec3 albedo;  // color of the material
};

inline vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}
#endif