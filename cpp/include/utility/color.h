#ifndef COLOR_UTILITY_H
#define COLOR_UTILITY_H

#include <embree3/common/math/vec3.h>


inline float Clamp(
    float color_channel,
    float min = 0.0f,
    float max = 1.0f)
{
    return (color_channel < min ? min : (color_channel > max ? max : color_channel));
}

inline embree::Vec3fa Clamp(
    const embree::Vec3fa &color)
{
    return embree::Vec3fa(
        Clamp(color.x),
        Clamp(color.y),
        Clamp(color.z));
}

inline float LinearToSRGB(
    float color_channel)
{
    return std::pow(color_channel, 1.0f / 2.2f);
}

inline embree::Vec3fa LinearToSRGB(
    const embree::Vec3fa &color)
{
    return embree::Vec3fa(
        LinearToSRGB(color.x),
        LinearToSRGB(color.y),
        LinearToSRGB(color.z));
}

inline float SRGBToLinear(
    float color_channel)
{
    return std::pow(color_channel, 2.2f);
}

inline embree::Vec3fa SRGBToLinear(
    const embree::Vec3fa &color)
{
    return embree::Vec3fa(
        SRGBToLinear(color.x),
        SRGBToLinear(color.y),
        SRGBToLinear(color.z));
}

inline int ToRGB(
    float color_channel)
{
    return static_cast<int>(Clamp(color_channel) * 255);
}

#endif // COLOR_UTILITY_H
