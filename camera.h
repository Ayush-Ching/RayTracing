#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:
        double aspect_ratio = 16.0 / 9.0;
        int image_height = 512;

        void render(const hittable& world, std::ostream& out) {
            initialize();

            out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for(int y=0; y<image_height; y++){
                std::clog << "\rScanlines remaining : " << (image_height - y) << ' ' << std::flush;
                
                for(int x=0; x<image_width; x++){
                    vec3 pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
                    vec3 ray_dir = pixel_center - center;
                    ray r(center, ray_dir);

                    color pixel_color = ray_color(r, world);
                    write_color(out, pixel_color);
                }
            }

            std::clog << "\rDone.                         \n";
        }

    private:
        int image_width;
        point3 center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void initialize() {
            image_width  = int(image_height * aspect_ratio) < 1 ? 1 : int(image_height * aspect_ratio);

            center = point3(0, 0, 0);

            double focal_length = 1.0;
            double viewport_height = 2.0;
            double viewport_width = viewport_height * (double(image_width) / image_height);

            // vectors across horizontal and vertical of viewport
            vec3 viewport_u = vec3(viewport_width, 0, 0);
            vec3 viewport_v = vec3(0, -viewport_height, 0);

            // delta vectors from one pixel to another on viewport
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // upper left pixel
            vec3 viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        color ray_color(const ray& r, const hittable& world) const {
            hit_record rec;
            if(world.hit(r, interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + color(1, 1, 1));
            }

            vec3 unit_dir = unit_vector(r.direction());
            double a = 0.5 * (unit_dir.y() + 1.0);
            return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.3, 0.5, 1.0);
        }
};

#endif