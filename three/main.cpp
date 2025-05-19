#include<iostream>
#include"ray.h"

vec3 color(const ray& r){
    vec3 unit_direction = unit_vector(r.direction());  // get the unit direction of the ray
    float t = 0.5 * (unit_direction.y() + 1.0);  // t is a value between 0 and 1
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);  // return a color based on t
}

int main() {
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
