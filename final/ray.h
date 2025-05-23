#ifndef RAY_H
#define RAY_H

#include"vec3.h"

class ray{
    public:
        ray(){}  // default constructor
        ray(const vec3 &a, const vec3 &b) {A = a; B = b;}  // constructor
        vec3 origin() const {return A;}  // returns the origin of the ray
        vec3 direction() const {return B;}  // returns the direction of the ray
        vec3 point_at_parameter(float t) const {return A + t * B;}  // returns the point at parameter t

        vec3 A;  // origin
        vec3 B;  // direction
};

#endif