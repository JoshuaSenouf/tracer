#include "render_helper.h"

#include "sphere.h"


Sphere::Sphere()
{

}


Sphere::Sphere(const std::string& tempName,
    double tempRadius,
    const Vector3& tempPosition,
    const BSDF& tempMaterial) :
    name(tempName),
    radius(tempRadius),
    position(tempPosition),
    material(tempMaterial)
{

}


float Sphere::computeIntersection(Ray& ray)
{
    Vector3 op = this->position - ray.getOrigin();
    float t, eps = EPSILON;
    float b = op.dot(ray.getDirection());

    float quadDis = (b * b) - op.dot(op) + (this->radius * this->radius);

    if(quadDis < 0)
        return 0;
    else
        quadDis = std::sqrt(quadDis);

    return (t = b - quadDis) >  eps ? t : ((t = b + quadDis) > eps ? t : 0);
}


std::string& Sphere::getName()
{
    return this->name;
}


double& Sphere::getRadius()
{
    return this->radius;
}


Vector3& Sphere::getPosition()
{
    return this->position;
}


BSDF& Sphere::getMaterial()
{
    return this->material;
}

void Sphere::setName(const std::string& tempName)
{
    this->name = tempName;
}


void Sphere::setRadius(double tempRadius)
{
    this->radius = tempRadius;
}


void Sphere::setPosition(const Vector3& tempPosition)
{
    this->position = tempPosition;
}


void Sphere::setMaterial(const BSDF& tempMaterial)
{
    this->material = tempMaterial;
}
