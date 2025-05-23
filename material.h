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
    metal(const vec3& a, float f) : albedo(a) {if(f>1) fuzz=f; else fuzz=1;}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);  
        scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
        attenuation = albedo;  // set the attenuation to the albedo
        return (dot(scattered.direction(), rec.normal) > 0);  
    }
    vec3 albedo;  // color of the material
    float fuzz;  // fuzziness factor
};

inline vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}

class dielectric: public material {
    public:
    dielectric(float ri) : ref_idx(ri) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = vec3(1.0, 1.0, 0.0);
        vec3 refracted;
        if(dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
        }
        else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            scattered = ray(rec.p, refracted);
            return true;
        }
        else {
            scattered = ray(rec.p, reflected);
            return false;
        }
    }
    float ref_idx;
};
        
    

#endif