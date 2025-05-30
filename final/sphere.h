#ifndef SPHERE_H
#define SPHERE_H

#include"hitable.h"

class material;  // forward declaration of the material class

class sphere: public hitable {
    public:
        sphere();
        sphere(vec3 cen, float r, material *m): center(cen), radius(r), mat_ptr(m) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        vec3 center;
        float radius;
        material *mat_ptr;  
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    
    if (discriminant > 0) {
        float temp = (-b - std::sqrt(discriminant)) / a;
         if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;  // set the material pointer
            return true;
        }
        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;  // set the material pointer
            return true;
        }
    }
    return false;
}

#endif