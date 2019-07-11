#ifndef COLOR_HELPER_H
#define COLOR_HELPER_H

#include "embree_helper.h"


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

inline float ToSrgb(float colorChannel)
{
    return std::pow(colorChannel, 1.0f / 2.2f);
}

inline embree::Vec3fa ToSrgb(const embree::Vec3fa &color)
{
    return embree::Vec3fa(ToSrgb(color.x),
        ToSrgb(color.y),
        ToSrgb(color.z));
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

inline int ToRgb(float colorChannel)
{
    return static_cast<int>(Clamp(colorChannel) * 255);
}

#endif // COLOR_HELPER_H
