#include "utils.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <fstream>

int main() {

    std::ofstream imageFS("img/image.ppm");

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

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