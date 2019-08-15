#include "position.h"

#include "render_helper.h"


PositionIntegrator::PositionIntegrator()
{
    _handle = "Position";
}

embree::Vec3f PositionIntegrator::GetPixelColor(Ray& ray,
    PixelSample& sample,
    SceneManager &scene,
    const RenderGlobals& globals)
{
    RTCIntersectContext intersectContext;
    rtcInitIntersectContext(&intersectContext);

    rtcIntersect1(scene._scene, &intersectContext, RTCRayHit_(ray));

    if (ray.instID == RTC_INVALID_GEOMETRY_ID)
    {
        // TODO: Hardcoded sky color value for now.
        return embree::Vec3f(0.7, 0.8, 0.9);
    }

    // We setup all the necessary data describing the shading point.
    ShadingPoint shadingPoint(SetupShadingPoint(scene, ray));

    return embree::normalize(shadingPoint.P);
}
