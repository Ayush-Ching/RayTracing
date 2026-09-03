#include "utils.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <fstream>

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if(world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_dir = unit_vector(r.direction());
    double a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.3, 0.5, 1.0);
}

int main() {

    std::ofstream imageFS("img/image.ppm");

    // Image
    double aspect_ratio = 16.0 / 9.0;
    int image_height = 512;
    int image_width  = int(image_height * aspect_ratio) < 1 ? 1 : int(image_height * aspect_ratio);

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width) / image_height);
    point3 camera_center = point3(0, 0, 0);

    // vectors across horizontal and vertical of viewport
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // delta vectors from one pixel to another on viewport
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // upper left pixel
    vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    // Render
    if(imageFS.is_open()) {

        imageFS << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for(int y=0; y<image_height; y++){
            std::clog << "\rScanlines remaining : " << (image_height - y) << ' ' << std::flush;
            
            for(int x=0; x<image_width; x++){
                vec3 pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
                vec3 ray_dir = pixel_center - camera_center;
                ray r(camera_center, ray_dir);

                color pixel_color = ray_color(r, world);
                write_color(imageFS, pixel_color);
            }
        }

        imageFS.close();
        std::clog << "\rDone.                         \n";
    }
    else {
        std::cerr << "Unable to open output image file location\n";
    }

    return 0;
}