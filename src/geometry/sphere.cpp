#include "sphere.h"


Sphere::Sphere()
{

}


Sphere::Sphere(float tempRadius, Vector3 tempPosition, Vector3 tempColor, Vector3 tempEmissiveColor, float tempMaterial) :
    radius(tempRadius), position(tempPosition), color(tempColor), emissiveColor(tempEmissiveColor), materialID(tempMaterial)
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
