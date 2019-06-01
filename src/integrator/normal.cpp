#include "normal.h"

#include "render_helper.h"


NormalIntegrator::NormalIntegrator()
{
    handle = "Normal";
}

embree::Vec3f NormalIntegrator::getPixelColor(Ray& ray,
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

    return embree::normalize(ray.Ng);
}