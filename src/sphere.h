#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
    sphere(const vec3& center, double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0, radius)), mat(mat) {}
    
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = center - r.origin();
        double a = dot(r.direction(), r.direction());
        double h = dot(r.direction(), oc);
        double c = dot(oc, oc) - radius*radius;
        double discriminant = h*h - a*c;
        
        if (discriminant < 0) {
            return false;
        } 
        else {
            double sqrtd = std::sqrt(discriminant);
            double t = (h - sqrtd) / a;
            
            // Find the nearest root in the range.
            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root))
                return false;
            }
            
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;
            
            return true;
        }
    }

    private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

#endif