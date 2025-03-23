#ifndef RAY_H
#define RAY_H

class ray {
    public:
    ray() : orig(point3(0,0,0)), dir(vec3(1,0,0)) {}
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
    
    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }
    
    point3 at(double t) const {
        return orig + t * dir;
    }

    private:
    point3 orig;
    vec3 dir;
};

#endif