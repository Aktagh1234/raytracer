#ifndef HITABLE
#define HITABLE

#include"ray.h"
#include"vec3.h"

class material;  // forward declaration of the material class

struct hit_record{
    float t;  // parameter at which the ray hits the object
    vec3 p;   // point of intersection
    vec3 normal;  // normal vector at the point of intersection
    material *mat_ptr;  // pointer to the material of the object
};

class hitable{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;  // pure virtual function
        // This function checks if the ray hits the object within the specified range of t values
};

#endif