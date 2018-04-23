#ifndef RAY_H
#define RAY_H

#include "vector.h"


class Ray
{
    public:
        Ray();
        Ray(const Vector3& tempOrigin,
            const Vector3& tempDirection);

        Vector3& getOrigin();
        Vector3& getDirection();

        void setOrigin(const Vector3& tempOrigin);
        void setDirection(const Vector3& tempDirection);

    private:
        Vector3 origin;
        Vector3 direction;
};

#endif // RAY_H
