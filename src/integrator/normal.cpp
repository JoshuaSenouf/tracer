#include "normal.h"

#include "render_helper.h"


NormalIntegrator::NormalIntegrator()
{
    _handle = "Normal";
}

embree::Vec3f NormalIntegrator::GetPixelColor(Ray& ray,
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

    return shadingPoint.N;
}
