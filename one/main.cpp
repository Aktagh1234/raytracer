#include<iostream>
#include"vec3.h"

int main() {
    int height= 400;
    int width= 800;
    std::cout<< "P3\n" << width << " " << height << "\n255\n";
    for (int y = height - 1; y >= 0; y--) {     // from top to bottom
        for (int x = 0; x < width; x++) {       // from left to right
            vec3 col(float(x) / float(width),float(y)/float(height),0.2);  // create a color vector
            int ir = int(255.99 * col[0]);           // convert to int
            int ig = int(255.99 * col[1]);           // 255.99 is the max value for 8-bit color
            int ib = int(255.99 * col[2]);           // 0.2 is the blue component
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
