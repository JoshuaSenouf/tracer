#include "ray.h"


Ray::Ray()
{

}

Ray::Ray(Vector3 tempOrigin, Vector3 tempDirection) :
    origin(tempOrigin), direction(tempDirection)
{

}
