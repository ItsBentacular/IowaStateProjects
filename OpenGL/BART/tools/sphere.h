#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "material.h"

//random info
// if ray and normal face in same dir, ray is inside the object; if ray and normal face in opposite dir, the ray is outside the object.
// you can check this by taking dot_product of the two vectors, if postive, ray is inside

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0,radius)), mat(mat) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = center - r.origin(); 
            auto a = r.direction().length_squared();
            auto h = dot_product(r.direction(), oc);
            auto c = oc.length_squared() - radius * radius;
            auto discriminant = h*h - a*c;

            if(discriminant < 0) {
                return false;
            }

            auto sqrtd = std::sqrt(discriminant);
            
            // find nearest root in acceptable range.
            auto root = (h - sqrtd) / a;
            if(!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if(!ray_t.surrounds(root)) {
                    return false;
                }
            }
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }

    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;
};

// makes bubbles automatically like you would a sphere, uses dielectric materials by default.
class bubble : public hittable {
    public:
        bubble(const point3& center, double outer_radius, double inner_radius, double ior) {
            auto outer_mat = make_shared<dielectric>(ior);
            auto inner_mat = make_shared<dielectric>(1.0 / ior);
            
            outer_sphere = make_shared<sphere>(center, outer_radius, outer_mat);
            inner_sphere = make_shared<sphere>(center, inner_radius, inner_mat);
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            if(outer_sphere->hit(r, interval(ray_t.min, closest_so_far), rec)) {
                hit_anything = true;
                closest_so_far = rec.t;
            }

            if(inner_sphere->hit(r,interval(ray_t.min, closest_so_far), rec)) {
                hit_anything = true;
            }

            return hit_anything;
        }


    private:
        shared_ptr<sphere> outer_sphere;
        shared_ptr<sphere> inner_sphere;
};



#endif