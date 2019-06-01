#include "position.h"

#include "render_helper.h"


PositionIntegrator::PositionIntegrator()
{
    handle = "Position";
}

embree::Vec3f PositionIntegrator::getPixelColor(Ray& ray,
    SceneManager &sceneManager,
    Randomizer& randEngine,
    int rayDepth)
{
    RTCIntersectContext intersectContext;
    rtcInitIntersectContext(&intersectContext);

    rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

    if (ray.geomID == RTC_INVALID_GEOMETRY_ID)
    {
        // TODO: Hardcoded sky color value for now.
        return embree::Vec3f(0.7, 0.8, 0.9);
    }

    return embree::normalize(ray.origin + ray.tfar * ray.direction);
}