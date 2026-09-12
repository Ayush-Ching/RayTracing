#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
            return false;
        }
};

class lambertian : public material {
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            vec3 scattered_direction = rec.normal + random_unit_vector();

            if(scattered_direction.near_zero()) scattered_direction = rec.normal;

            scattered = ray(rec.p, scattered_direction);
            attenuation = albedo;
             return true;
        }

    private:
        color albedo;
};

#endif