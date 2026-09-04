#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:
        double aspect_ratio = 1.0;
        int image_height = 100;
        int samples_per_pixel = 10;

        void render(const hittable& world, std::ostream& out) {
            initialize();

            out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for(int y=0; y<image_height; y++){
                std::clog << "\rScanlines remaining : " << (image_height - y) << ' ' << std::flush;
                
                for(int x=0; x<image_width; x++){
                    color pixel_color(0, 0, 0);

                    // randomly sample a square around our pixel
                    for(int sample = 1; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(x, y);
                        pixel_color += ray_color(r, world);
                    }
                    
                    // sample the center of the pixel
                    vec3 pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
                    vec3 ray_dir = pixel_center - center;
                    ray r(center, ray_dir);
                    pixel_color += ray_color(r, world);

                    write_color(out, pixel_sample_scale * pixel_color);
                }
            }

            std::clog << "\rDone.                         \n";
        }

    private:
        int image_width;
        double pixel_sample_scale;
        point3 center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void initialize() {
            image_width  = int(image_height * aspect_ratio) < 1 ? 1 : int(image_height * aspect_ratio);

            pixel_sample_scale = 1.0 / samples_per_pixel;

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

        ray get_ray(int i, int j) const {
            vec3 offset = sample_square();
            vec3 pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

            vec3 ray_origin = center;
            vec3 ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const {
            // a random vector in a 1x1 square.
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        color ray_color(const ray& r, const hittable& world) const {
            hit_record rec;

            if(world.hit(r, interval(0, infinity), rec)) {
                vec3 direction = random_on_hemisphere(rec.normal);
                return 0.5 * ray_color(ray(rec.p, direction), world);
            }

            vec3 unit_dir = unit_vector(r.direction());
            double a = 0.5 * (unit_dir.y() + 1.0);
            return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.3, 0.5, 1.0);
        }
};

#endif