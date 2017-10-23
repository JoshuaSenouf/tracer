#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#define M_PI 3.14159265358979323846f
#define M_2PI 6.28318530717958647692f
#define M_1_PI 0.318309886183790671538f
#define M_1_180 0.005555555555555555556f

#include "vector.h"


inline float clamp(float x)
{
    return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}


inline float convertToSRGB(float x)
{
    return pow(x, 1.0f / 2.2f);
}


inline float convertToLinear(float x)
{
    return pow(x, 2.2f);
}


inline Vector3 clamp(Vector3 &tempVector)
{
    return Vector3(clamp(tempVector.x), clamp(tempVector.y), clamp(tempVector.z));
}


inline Vector3 convertToSRGB(Vector3 &tempVector)
{
    return Vector3(convertToSRGB(tempVector.x), convertToSRGB(tempVector.y), convertToSRGB(tempVector.z));
}


inline Vector3 convertToLinear(Vector3 &tempVector)
{
    return Vector3(convertToLinear(tempVector.x), convertToLinear(tempVector.y), convertToLinear(tempVector.z));
}


inline int convertToRGB(float x)
{
    return int(clamp(x) * 255);
}


inline float degreesToRadians(float degreesAngle)
{
    return degreesAngle * (M_PI / 180.0f);
}


inline float radiansToDegrees(float radiansAngle)
{
    return radiansAngle * (180.0f / M_PI);
}

#endif // MATH_HELPER_H
