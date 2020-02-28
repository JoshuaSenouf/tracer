#ifndef COLOR_HELPER_H
#define COLOR_HELPER_H

#include <embree3/common/math/vec3.h>


inline float Clamp(float colorChannel)
{
    return colorChannel < 0.0f ? 0.0f : colorChannel > 1.0f ? 1.0f : colorChannel;
}

inline embree::Vec3fa Clamp(const embree::Vec3fa &color)
{
    return embree::Vec3fa(Clamp(color.x),
        Clamp(color.y),
        Clamp(color.z));
}

inline float ToSRGB(float colorChannel)
{
    return std::pow(colorChannel, 1.0f / 2.2f);
}

inline embree::Vec3fa ToSRGB(const embree::Vec3fa &color)
{
    return embree::Vec3fa(ToSRGB(color.x),
        ToSRGB(color.y),
        ToSRGB(color.z));
}

inline float ToLinear(float colorChannel)
{
    return std::pow(colorChannel, 2.2f);
}

inline embree::Vec3fa ToLinear(const embree::Vec3fa &color)
{
    return embree::Vec3fa(ToLinear(color.x),
        ToLinear(color.y),
        ToLinear(color.z));
}

inline int ToRGB(float colorChannel)
{
    return static_cast<int>(Clamp(colorChannel) * 255);
}

#endif // COLOR_HELPER_H
