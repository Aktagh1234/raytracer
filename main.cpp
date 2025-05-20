#include<iostream>
#include"ray.h"

float hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;  // vector from the ray origin to the sphere center
    float a = dot(r.direction(), r.direction());  // dot product of the ray direction with itself
    float b = 2.0 * dot(oc, r.direction());  // dot product of oc and the ray direction
    float c = dot(oc, oc) - radius * radius;  // dot product of oc with itself minus the square of the radius
    float discriminant = b * b - 4 * a * c;  // discriminant of the quadratic equation
    if (discriminant < 0) {
        return -1.0;  // returns false if the ray does not hit the sphere
    }
    else{
        return(-b - sqrt(discriminant)) / (2.0 * a);  // returns the t value of the intersection
    }
}

vec3 sphere;
float sphere_radius;

vec3 color(const ray& r){
    float t = hit_sphere(sphere, sphere_radius, r);  // check if the ray hits the sphere
    //material color
    if (t > 0.0) {
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, 0));  // normal vector at the hit point
        // Normalize N to be in range [0, 1]
        vec3 normalized = 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
        // Use HSV-to-RGB-like trick to spread colors
        return vec3(normalized.x(), normalized.y(), 1.0 - normalized.z());
    }
    //sky color
    vec3 unit_direction = unit_vector(r.direction());  // get the unit direction of the ray
    t = 0.5 * (unit_direction.y() + 1.0);  // t is a value between 0 and 1
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);  // return a color based on t
}

int main() {
    sphere=vec3(0,0,-1);  // set the center of the sphere
    sphere_radius= 0.5;  // set the radius of the sphere
    int height= 400;
    int width= 800;
    std::cout<< "P3\n" << width << " " << height << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);  // lower left corner of the image
    vec3 horizontal(4.0, 0.0, 0.0);           // horizontal vector
    vec3 vertical(0.0, 2.0, 0.0);             // vertical vector
    vec3 origin(0.0, 0.0, 0.0);               // origin of the camera
    for (int y = height - 1; y >= 0; y--) {     // from top to bottom
        for (int x = 0; x < width; x++) {       // from left to right
            float u = float(x) / float(width);   // u coordinate
            float v = float(y) / float(height);  // v coordinate
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);  // create a ray
            vec3 col = color(r);
            //vec3 col(float(x) / float(width),float(y)/float(height),0.2);  // create a color vector
            int ir = int(255.99 * col[0]);           // convert to int
            int ig = int(255.99 * col[1]);           // 255.99 is the max value for 8-bit color
            int ib = int(255.99 * col[2]);           // 0.2 is the blue component
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
