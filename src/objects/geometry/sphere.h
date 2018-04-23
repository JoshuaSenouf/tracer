#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "ray.h"
#include "material.h"


class Sphere
{
    public:
        Sphere();
        Sphere(const std::string& tempName,
            double tempRadius,
            const Vector3& tempPosition,
            const BSDF& tempMaterial);

        float computeIntersection(Ray& ray);

        std::string& getName();
        double& getRadius();
        Vector3& getPosition();
        BSDF& getMaterial();
        
        void setName(const std::string& tempName);
        void setRadius(double tempRadius);
        void setPosition(const Vector3& tempPosition);
        void setMaterial(const BSDF& tempMaterial);

    private:
        std::string name;
        double radius;
        Vector3 position;
        BSDF material;
};

#endif // SPHERE_H
