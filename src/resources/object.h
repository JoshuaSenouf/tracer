#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "vector.h"


struct RayObject
{
        Vector3 origin;
        Vector3 direction;

        RayObject(Vector3 tempOrigin, Vector3 tempDirection) : origin(tempOrigin), direction(tempDirection)
        {

        }
};


struct SphereObject
{
        float radius;

        Vector3 position;
        Vector3 color;
        Vector3 emissiveColor;

        materialType material;
};


#endif // OBJECT_H
