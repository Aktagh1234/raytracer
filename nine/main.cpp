#include<iostream>
#include"hitable_list.h"
#include"sphere.h"
#include <cfloat>
#include "camera.h"
#include "material.h"

vec3 color(const ray& r, hitable *world, int depth){
    hit_record rec;  // create a hit_record object
    if (world->hit(r,0.001, FLT_MAX, rec)) {
        //vec3 target = rec.p + rec.normal + random_in_unit_sphere();  // get a random point in the unit sphere
        //Drawing out spheres
        //return 0.5 * color(ray(rec.p, target - rec.p), world);  // return a color based on the normal vector
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth+1);  
        }
        else{
            return vec3(0,0,0);  // return black if the ray is not scattered
        }
    }
    else{
        //sky
        vec3 unit_direction = unit_vector(r.direction());  // get the unit direction of the ray
        float t = 0.5 * (unit_direction.y() + 1.0);  // t is a value between 0 and 1
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);  // return a color based on t
    }
}

int main() {
    //sphere=vec3(0,0,-1);  // set the center of the sphere
    //sphere_radius= 0.5;  // set the radius of the sphere
    int height= 400;
    int width= 800;
    int ns=100;  // number of samples per pixel
    std::cout<< "P3\n" << width << " " << height << "\n255\n";

    hitable *list[5];  // list of hitable objects
    camera cam;
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1,0.2,0.5)));  // create a sphere object
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8,0.8,0.0)));  // create a large sphere object
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8,0.6,0.2),0.2));  // create a sphere object
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));  // create a sphere object
    list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));  // create a sphere object
    hitable *world = new hitable_list(list, 5);  // create a hitable list with the spheres
    for (int y = height - 1; y >= 0; y--) {     // from top to bottom
        for (int x = 0; x < width; x++) {  
            vec3 col(0,0,0);
            for (int s=0; s<ns; s++) {  // loop over the number of samples
                float u = float(x+drand48()) / float(width);   // u coordinate
                float v = float(y+drand48()) / float(height);  // v coordinate
                ray r = cam.get_ray(u, v);  // create a ray using the camera
                vec3 p = r.point_at_parameter(2.0);  
                col += color(r, world, 0);  // get the color from the ray, start with depth 0
            }
            col /= float(ns);  // average the color over the number of samples
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));  // gamma correction
            int ir = int(255.99 * col[0]);           // convert to int
            int ig = int(255.99 * col[1]);           // 255.99 is the max value for 8-bit color
            int ib = int(255.99 * col[2]);           // 0.2 is the blue component
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
