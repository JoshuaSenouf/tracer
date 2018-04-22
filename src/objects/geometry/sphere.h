#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "ray.h"
#include "material.h"


class Sphere
{
    public:
        std::string name;
        double radius;
        Vector3 position;
        BSDF material;

        Sphere();
        Sphere(const std::string& tempName,
            double tempRadius,
            const Vector3& tempPosition,
            const BSDF& tempMaterial);

        float computeIntersection(const Ray& ray);

    private:
};

#endif // SPHERE_H
