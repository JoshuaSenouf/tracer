#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include "vector.h"


enum INTEGRATOR_ID {
    UDPT,
    DIFFUSE,
    OCCLUSION,
    DEBUG,
};

inline float clamp(float colorChannel)
{
    return colorChannel < 0.0f ? 0.0f : colorChannel > 1.0f ? 1.0f : colorChannel;
}

inline Vector3 clamp(const Vector3 &color)
{
    return Vector3(clamp(color.x),
        clamp(color.y),
        clamp(color.z));
}

inline float convertToSRGB(float colorChannel)
{
    return std::pow(colorChannel, 1.0f / 2.2f);
}

inline Vector3 convertToSRGB(const Vector3 &color)
{
    return Vector3(convertToSRGB(color.x),
        convertToSRGB(color.y),
        convertToSRGB(color.z));
}

inline float convertToLinear(float colorChannel)
{
    return std::pow(colorChannel, 2.2f);
}

inline Vector3 convertToLinear(const Vector3 &color)
{
    return Vector3(convertToLinear(color.x),
        convertToLinear(color.y),
        convertToLinear(color.z));
}

inline int convertToRGB(float colorChannel)
{
    return int(clamp(colorChannel) * 255);
}

#endif // RENDER_HELPER_H
