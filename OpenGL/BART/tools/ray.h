#ifndef RAY_H
#define RAY_H

#include "utilities.h"
#include "vec3.h"

// a ray is a function P(t) = A + tb, P is a 3D position along a line in 3D, A is the ray origin, b is ray direction, t is the point along the ray

class ray {
    public:
        ray() {}

        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        const point3& origin() const {return orig; }
        const vec3& direction() const {return dir; }

        point3 at(double t) const {
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif