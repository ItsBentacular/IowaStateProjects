#include "../tools/utilities.h"
#include "../tools/hittable.h"
#include "../tools/hittable_list.h"
#include "../tools/sphere.h"
#include "../tools/camera.h"
#include "../tools/material.h"

int main() {
    hittable_list world;
    
    auto material_ground = make_shared<lambertian>(color(0.2, 0.6, 0.2));
    auto material_metal_right = make_shared<metal>(color(0.8,0.8,0.8), 0.1);
    auto material_dielectric_left = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00/1.50);
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5, material_center));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100, material_ground));
    world.add(make_shared<sphere>(point3(-1.0,0.0,-1.0), 0.5, material_dielectric_left));
    world.add(make_shared<sphere>(point3(-1.0,0.0,-1.0), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3(1.0,0.0,-1.0), 0.5, material_metal_right));
    /**
    auto R = std::cos(pi/4);

    auto material_left  = make_shared<lambertian>(color(0,0,1));
    auto material_right = make_shared<lambertian>(color(1,0,0));

    world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    world.add(make_shared<sphere>(point3( R, 0, -1), R, material_right));
    */

    world.add(make_shared<bubble>(point3(0,0.2,0.7), 0.5, 0.3, 1.5));

    camera cam;

    cam.aspect_ratio - 16/9;
    cam.image_width = 1600;
    cam.samples_per_pixel = 150;
    cam.max_depth = 150;

    cam.vfov = 90;
    cam.lookfrom = point3(0,0.4,1.3);
    cam.lookat = point3(0,0,-1);
    cam.vup = vec3(0,1,0);

    cam.defocus_angle = 0.0;
    cam.focus_dist = 10.0;

    cam.render(world);
    
}