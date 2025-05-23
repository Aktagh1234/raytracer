#ifndef VEC3_H
#define VEC3_H

#include<math.h>
#include<stdlib.h>
#include<iostream>


class vec3{
public:
    vec3(){}                                                              // default constructor
    vec3(float e0, float e1, float e2) {e[0] = e0; e[1] = e1; e[2] = e2;} // constructor

    inline float x() const {return e[0];}   // accessors
    inline float y() const {return e[1];}
    inline float z() const {return e[2];}
    inline float r() const {return e[0];}
    inline float g() const {return e[1];}
    inline float b() const {return e[2];}

    inline const vec3& operator+() const {return *this;}    //returns unchanged vector
    inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}   //returns negated vector
    inline float operator[](int i) const {return e[i];}     //read-only access
    inline float& operator[](int i) {return e[i];}      //read-write access

    inline vec3& operator+=(const vec3 &v2);    //adds v2 to this vector
    inline vec3& operator-=(const vec3 &v2);    //subtracts v2 from this vector
    inline vec3& operator*=(const vec3 &v2);    //multiplies this vector by v2
    inline vec3& operator/=(const vec3 &v2);    //divides this vector by v2
    inline vec3& operator*=(const float t);     //multiplies this vector by scalar t
    //inline vec3& operator/=(const float t);     //divides this vector by scalar t
    inline vec3& operator/=(const float t) {
        return *this *= 1/t;   //divides this vector by scalar t
    }
    inline float length() const {  // returns the length of the vector
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }
    inline float squared_length() const {  // returns the squared length of the vector
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    inline void make_unit_vector(); // declaration of make_unit_vector
    float e[3];     // array of 3 floats
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {  // input operator
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {  // output operator
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void vec3::make_unit_vector(){   // normalizes the vector i.e the length of the vector is 1
    float k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {  // vector addition
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {  // vector subtraction
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {  // vector multiplication
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {  // vector division
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3 &v) {  // scalar multiplication
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(float t, const vec3 &v) {  // scalar division
    return vec3(t / v.e[0], t / v.e[1], t / v.e[2]);
}

inline vec3 operator*(const vec3 &v, float t) {  // scalar multiplication
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(const vec3 &v, float t) {  // scalar division
    return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const vec3 &v1, const vec3 &v2) {  // dot product
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {  // cross product
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                 v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                 v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline vec3& vec3::operator+=(const vec3 &v2) {  // vector addition assignment
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v2) {  // vector subtraction assignment
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v2) {  // vector multiplication assignment
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v2) {  // vector division assignment
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const float t) {  // scalar multiplication assignment
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;  
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else {
        return false;
    }
}

#endif