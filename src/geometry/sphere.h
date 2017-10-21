#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"


class Sphere
{
    public:
        std::string name;
        float radius;
        Vector3 position;
        Vector3 color;
        Vector3 emissiveColor;
        float materialID;

        Sphere();
        Sphere(float tempRadius, Vector3 tempPosition, Vector3 tempColor, Vector3 tempEmissiveColor, float tempMaterial);

    private:
};

#endif // SPHERE_H
