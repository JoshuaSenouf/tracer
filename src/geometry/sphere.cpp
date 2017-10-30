#include "sphere.h"


Sphere::Sphere()
{

}


Sphere::Sphere(const std::string& tempName, float tempRadius, const Vector3& tempPosition, const BSDF& tempMaterial) :
    name(tempName), radius(tempRadius), position(tempPosition), material(tempMaterial)
{

}


float Sphere::computeIntersection(const Ray& ray)
{
    Vector3 op = position - ray.origin;
    float t, eps = EPSILON;
    float b = op.dot(ray.direction);

    float quadDis = (b * b) - op.dot(op) + (radius * radius);

    if(quadDis < 0)
        return 0;
    else
        quadDis = std::sqrt(quadDis);

    return (t = b - quadDis) >  eps ? t : ((t = b + quadDis) > eps ? t : 0);
}
