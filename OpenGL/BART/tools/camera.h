#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

// 16/9 aspect ratio = 1.7778
class camera {
    public:
        // public camera vars here
        double aspect_ratio = 1.0; // ratio of image width/height
        int image_width = 100;  // rendered image width in pixel count.
        int samples_per_pixel = 10; // count of samples for each pixel, used for anti-aliasing
        int max_depth = 10; // max number of ray bounces in scene

        double vfov = 90; // FOV/ Vertical view angle
        point3 lookfrom = point3(0,0,0); // point camera is looking from
        point3 lookat = point3(0,0,-1); // point camera is looking at
        vec3 vup = vec3(0,1,0); // camera up dir

        double defocus_angle = 0; // variation angles of rays through each pixel
        double focus_dist = 10; // distance from lookfrom to plane of focus

        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for(int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for(int i = 0; i < image_width; i++) {
                    color pixel_color(0,0,0);
                    for(int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                } 
            }
            std::clog << "\r Image Complete.             \n";
        }

    private:
        // private camera vars here
        int image_height; //render image height
        double pixel_samples_scale; // color scale factor for the sum of pixel samples.
        point3 center; // camera center
        point3 pixel00_loc; // location of the pixel 0,0
        vec3 pixel_delta_u; // offset to the pixel to the right
        vec3 pixel_delta_v; // offset to the pixel below
        vec3 u, v, w; // camera frame basis vectors
        vec3 defocus_disk_u; // defocus disk horizontal radius
        vec3 defocus_disk_v; // defocus disk vertical radius
        void initialize() {
            image_height = int(image_width/aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0/samples_per_pixel;

            center = lookfrom;

            //viewport dimension calculations
            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta/2);
            auto viewport_height = 2 * h * focus_dist;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            // calc unit basis vectors for camera coord frame
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross_product(vup,w));
            v = cross_product(w,u);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = viewport_height * u;
            auto viewport_v = viewport_height * -v;

            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / image_width; // horiz viewport vector
            pixel_delta_v = viewport_v / image_height; // vertical viewport vector

            //calculate the upper left pixel location
            auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

            //calculate camera defocus disk vectors

            auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_v = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }

        vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        //vec3 sample_disk(double radius) const {
        // Returns a random point in the unit (radius 0.5) disk centered at the origin.
        //return radius * random_in_unit_disk();
        //}

        // construct a camera ray from the origin and direct at randomly sampled points around pixel i , j.
        ray get_ray(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

            auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        // returns a random point in the camera defocus disk
        point3 defocus_disk_sample() const {
            auto p = random_in_unit_disk();
            return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
        }

        // for ray_color, linear interpolation (scaling colors), or lerp, is always in the form of: blendedValue = (1 - a) * startValue + a * endValue, a going from zero to one. 0.0 is white, 1.0 is blue
        color ray_color(const ray& r, int depth, const hittable& world) const {
            hit_record rec;
            if(depth <= 0) {
                return color(0,0,0);
            }
            if(world.hit(r,interval(0.001, infinity), rec)) { // the 0.001 helps prevent random floating point rounding errors with the rays.
                ray scattered;
                color attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, depth-1, world);
                return color(0,0,0);
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
        }

};

#endif