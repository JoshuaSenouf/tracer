#include "sphere.h"


Sphere::Sphere()
{

}


Sphere::Sphere(float tempRadius, Vector3 tempPosition, Vector3 tempColor, Vector3 tempEmissiveColor, float tempMaterial) :
    radius(tempRadius), position(tempPosition), color(tempColor), emissiveColor(tempEmissiveColor), materialID(tempMaterial)
{

}
