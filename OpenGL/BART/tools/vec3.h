#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

// vec3 object
class vec3 {
    public:
        double e[3];

        // default constructor for vec3
        vec3() : e{0,0,0} {}
        //constructor to specify coordinates in vec3 
        vec3(double e1, double e2, double e3) : e{e1, e2, e3} {}

        double x() const {return e[0]; }
        double y() const {return e[1]; }
        double z() const {return e[2]; }

        // negative
        vec3 operator-() const {
            return vec3(-e[0], -e[1], -e[2]);
        }

        // does not return a reference, and for const values only
        double operator[] (int i) const {
            return e[i];
        }
        
        // returns a reference to a double, allowing the modification of the value
        double& operator[] (int i) {
            return e[i];
        }

        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(double d) {
            return *this *= 1/d;
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }

        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }

};

using point3 = vec3;

//inlines are here in order to be able to do simple math functions on our vec3 object without having to make annoying methods/calls for every scenario.

inline std::ostream& operator <<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 & v) {
    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot_product(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross_product(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}
//generate a random vector inside unit sphere
// normalize said vector to extend it to the sphere's surface
// invert the vector if it falls on the wrong hemisphere.

inline vec3 random_unit_vector() {
    while(true) {
        auto p = vec3::random(-1,1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq &&  lensq <= 1) {
            return p / sqrt(lensq);
        }
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if(dot_product(on_unit_sphere, normal) > 0.0) { // in same hemisphere as normal input
        return on_unit_sphere; 
    } else {
        return -on_unit_sphere;
    } 

}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot_product(v,n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot_product(-uv,n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_parallel + r_out_perp;
}

inline vec3 random_in_unit_disk() {
    while(true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if(p.length_squared() < 1) {
            return p;
        }
    }
}
        

#endif