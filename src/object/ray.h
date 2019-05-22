#ifndef RAY_H
#define RAY_H

#include "camera.h"
#include "randomizer.h"
#include "embree_helper.h"


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
    __forceinline Ray(const Camera& camera,
        int posX,
        int posY,
        Randomizer& randEngine,
        float tnear = 0,
        float tfar = std::numeric_limits<float>::infinity(),
        float time = 0,
        int mask = -1,
        unsigned int geomID = RTC_INVALID_GEOMETRY_ID,
        unsigned int primID = RTC_INVALID_GEOMETRY_ID,
        unsigned int instID = RTC_INVALID_GEOMETRY_ID)
        : tfar(tfar),
        mask(mask),
        primID(primID),
        geomID(geomID),
        instID(instID)
    {
        embree::Vec3fa horizontalAxis(embree::normalize(embree::cross(camera._front, camera._up)));
        embree::Vec3fa verticalAxis(embree::normalize(embree::cross(horizontalAxis, camera._front)));
        embree::Vec3fa middle(camera._position + camera._front);
        embree::Vec3fa horizontal(horizontalAxis * std::tan(camera._fov.x * 0.5f * (M_PI / 180)));
        embree::Vec3fa vertical(verticalAxis * std::tan(camera._fov.y * -0.5f * (M_PI / 180)));

        float pointX((((camera._doJitter ? randEngine.getRandomFloat() : 0.0f) - 0.5f) + posX)
            / (camera._resolution.x - 1.0f));
        float pointY((((camera._doJitter ? randEngine.getRandomFloat() : 0.0f) - 0.5f) + posY)
            / (camera._resolution.y - 1.0f));

        embree::Vec3fa pointOnPlane(camera._position
            + ((middle
            + (horizontal * ((2.0f * pointX) - 1.0f))
            + (vertical * ((2.0f * pointY) - 1.0f))
            - camera._position)
            * camera._focalDistance));

        embree::Vec3fa aperturePoint(camera._position);
        if (camera._apertureRadius > 0.0f)
        {
            float randomizedAngle(2.0f * M_PI * randEngine.getRandomFloat());
            float randomizedRadius(camera._apertureRadius * std::sqrt(randEngine.getRandomFloat()));
            float apertureX(std::cos(randomizedAngle) * randomizedRadius);
            float apertureY(std::sin(randomizedAngle) * randomizedRadius);

            aperturePoint = camera._position + (horizontalAxis * apertureX) + (verticalAxis * apertureY);
        }

        origin = embree::Vec3fa(aperturePoint, tnear);
        direction = embree::Vec3fa(embree::normalize(pointOnPlane - aperturePoint), time);
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
