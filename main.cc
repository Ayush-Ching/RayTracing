#include "utils.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <fstream>

int main() {

    std::ofstream imageFS("img/image.ppm");

    // World
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.0 / 1.33);
    auto material_right  = make_shared<metal>(color(0.8, 0.8, 0.4), 1.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -2.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.2,    0.0, -1.5),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.2,    0.0, -1.5),   0.5, material_right));
    
    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_height = 512;
    cam.samples_per_pixel = 100;
    cam.max_depth = 10;
    
    // Render
    if(imageFS.is_open()) {
        cam.render(world, imageFS);
        imageFS.close();
    }
    else {
        std::cerr << "Unable to open output image file location\n";
    }

    return 0;
}