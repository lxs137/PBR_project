//
// Created by lxs on 17-3-22.
//

#include "plane.h"

BBox Plane::get_BBox() {
    return BBox(Point3D(-INFINITY, -INFINITY, -INFINITY), Point3D(INFINITY, INFINITY, INFINITY));
}
bool Plane::intersect(const Ray &ray, float &t_hit, IntersectInfo &info) {
    // t = (plane.p*plane.n - ray.o*plane.n) / (ray.d*plane.n)
    float parallel_test = Dot(ray.d, this->n);
    if(std::fabs(parallel_test) < 1e-5)
        return false;
    else
    {
        float t = Dot((this->p - ray.o), this->n) / Dot(ray.d, this->n);
        if(t > this->Epsilon && t > ray.min_t && t < ray.max_t)
        {
            info.hit_n = this->n;
            info.hit_p = ray(t);
            info.shape = this;
            t_hit = t;
            return true;
        } else
            return false;
    }
}
bool Plane::intersectP(const Ray &ray) {
    // t = (plane.p*plane.n - ray.o*plane.n) / (ray.d*plane.n)
    float parallel_test = Dot(ray.d, this->n);
    if(std::fabs(parallel_test) < 1e-5)
        return false;
    else
    {
        float t = Dot((this->p - ray.o), this->n) / Dot(ray.d, this->n);
        if(t > this->Epsilon && t > ray.min_t && t < ray.max_t)
        {
            return true;
        } else
            return false;
    }
}
