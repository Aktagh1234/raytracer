#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera {
    public:
    camera() {
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }
    ray get_ray(float u, float v) {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }
    vec3 lower_left_corner, horizontal, vertical, origin;
};

#endif