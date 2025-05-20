#ifndef HITABLE
#define HITABLE

#include"ray.h"

struct hit_record{
    float t;  // parameter at which the ray hits the object
    vec3 p;   // point of intersection
    vec3 normal;  // normal vector at the point of intersection
};

class hitable{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;  // pure virtual function
        // This function checks if the ray hits the object within the specified range of t values
};

#endif