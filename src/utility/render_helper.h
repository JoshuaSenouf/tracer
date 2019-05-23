#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include "embree_helper.h"


enum INTEGRATOR_ID {
    UDPT,
    DIFFUSE,
    OCCLUSION,
    POSITION,
    NORMAL,
    DEBUG,
};

inline float clamp(float colorChannel)
{
    return colorChannel < 0.0f ? 0.0f : colorChannel > 1.0f ? 1.0f : colorChannel;
}

inline embree::Vec3fa clamp(const embree::Vec3fa &color)
{
    return embree::Vec3fa(clamp(color.x),
        clamp(color.y),
        clamp(color.z));
}

inline float toSRGB(float colorChannel)
{
    return std::pow(colorChannel, 1.0f / 2.2f);
}

inline embree::Vec3fa toSRGB(const embree::Vec3fa &color)
{
    return embree::Vec3fa(toSRGB(color.x),
        toSRGB(color.y),
        toSRGB(color.z));
}

inline float toLinear(float colorChannel)
{
    return std::pow(colorChannel, 2.2f);
}

inline embree::Vec3fa toLinear(const embree::Vec3fa &color)
{
    return embree::Vec3fa(toLinear(color.x),
        toLinear(color.y),
        toLinear(color.z));
}

inline int toRGB(float colorChannel)
{
    return static_cast<int>(clamp(colorChannel) * 255);
}

#endif // RENDER_HELPER_H
