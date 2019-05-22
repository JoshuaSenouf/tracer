#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#define M_2PI 6.28318530717958647692f
#define M_1_180 0.005555555555555555556f

#include <math.h>


inline float degToRad(float degAngle)
{
    return degAngle * (M_PI / 180.0f);
}

inline float radToDeg(float radAngle)
{
    return radAngle * (180.0f / M_PI);
}

#endif // MATH_HELPER_H
