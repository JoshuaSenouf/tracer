#ifndef RAY_H
#define RAY_H

#include "embree_helper.h"


// WIP, from Embree's sources.
struct Ray
{
    embree::Vec3fa origin;
    embree::Vec3fa direction;

    float tfar;
    unsigned int mask;
    unsigned int id;
    unsigned int flags;

    embree::Vec3f Ng;
    float u;
    float v;
    unsigned int primID;
    unsigned int geomID;
    unsigned int instID;

    __forceinline Ray(const embree::Vec3fa &org,
        const embree::Vec3fa &dir,
        float tnear = 0,
        float tfar = std::numeric_limits<float>::infinity(),
        float time = 0,
        int mask = -1,
        unsigned int geomID = RTC_INVALID_GEOMETRY_ID,
        unsigned int primID = RTC_INVALID_GEOMETRY_ID,
        unsigned int instID = RTC_INVALID_GEOMETRY_ID)
        : origin(org, tnear),
        direction(dir, time),
        tfar(tfar),
        mask(mask),
        primID(primID),
        geomID(geomID),
        instID(instID)
    {
    }
};

__forceinline RTCRay *RTCRay_(Ray &ray)
{
    return (RTCRay *)&ray;
}

__forceinline RTCRayHit *RTCRayHit_(Ray &ray)
{
    return (RTCRayHit *)&ray;
}

#endif // RAY_H
