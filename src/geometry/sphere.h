#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "material.h"


class Sphere
{
    public:
        float radius;
        Vector3 position;
        Vector3 color;
        Vector3 emissiveColor;
        materialType material;

        Sphere();
        Sphere(float tempRadius, Vector3 tempPosition, Vector3 tempColor, Vector3 tempEmissiveColor, materialType tempMaterial);

    private:
};

#endif // SPHERE_H
