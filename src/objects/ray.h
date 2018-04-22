#ifndef RAY_H
#define RAY_H

#include "vector.h"


class Ray
{
    public:
        Vector3 origin;
        Vector3 direction;

        Ray();
        Ray(Vector3 tempOrigin,
            Vector3 tempDirection);

    private:
};

#endif // RAY_H
