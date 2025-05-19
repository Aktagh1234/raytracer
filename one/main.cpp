#include<iostream>
#include"vec3.h"

int main() {
    int height= 400;
    int width= 800;
    std::cout<< "P3\n" << width << " " << height << "\n255\n";
    for (int y = height - 1; y >= 0; y--) {     // from top to bottom
        for (int x = 0; x < width; x++) {       // from left to right
            float r = float(x) / float(width);  // normalize x to [0, 1]
            float g = float(y) / float(height); // normalize y to [0, 1]
            float b = 0.2f;                     // fixed blue value
            int ir = int(255.99 * r);           // convert to int
            int ig = int(255.99 * g);           // 255.99 is the max value for 8-bit color
            int ib = int(255.99 * b);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
