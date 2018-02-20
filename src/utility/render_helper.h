#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#define EPSILON 0.001f

#include "vector.h"


struct cameraData
{
    Vector3 position;
    float yaw;
    float pitch;
    float fov;
    float apertureRadius;
    float focalDistance;
};

struct settingsData
{
    Vector3 skyColor;
};


inline float clamp(float x)
{
    return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}


inline Vector3 clamp(const Vector3 &tempVector)
{
    return Vector3(clamp(tempVector.x), clamp(tempVector.y), clamp(tempVector.z));
}


inline float convertToSRGB(float x)
{
    return std::pow(x, 1.0f / 2.2f);
}


inline Vector3 convertToSRGB(const Vector3 &tempVector)
{
    return Vector3(convertToSRGB(tempVector.x), convertToSRGB(tempVector.y), convertToSRGB(tempVector.z));
}


inline float convertToLinear(float x)
{
    return std::pow(x, 2.2f);
}


inline Vector3 convertToLinear(const Vector3 &tempVector)
{
    return Vector3(convertToLinear(tempVector.x), convertToLinear(tempVector.y), convertToLinear(tempVector.z));
}


inline int convertToRGB(float x)
{
    return int(clamp(x) * 255);
}


#endif // RENDER_HELPER_H
