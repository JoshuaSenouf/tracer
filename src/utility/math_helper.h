#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#define M_PI 3.14159265358979323846f
#define M_2PI 6.28318530717958647692f
#define M_1_PI 0.318309886183790671538f
#define M_1_180 0.005555555555555555556f

#include "vector.h"


inline float degreesToRadians(float degreesAngle)
{
    return degreesAngle * (M_PI / 180.0f);
}

inline float radiansToDegrees(float radiansAngle)
{
    return radiansAngle * (180.0f / M_PI);
}

#endif // MATH_HELPER_H
