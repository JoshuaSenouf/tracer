#include "debug.h"


DebugIntegrator::DebugIntegrator()
{
    handle = "Debug";
}

Vector3 DebugIntegrator::getPixelColor(Ray& ray,
    SceneManager &scene,
    Randomizer& randEngine,
    int rayDepth)
{
    RTCIntersectContext intersectContext;
    rtcInitIntersectContext(&intersectContext);

    rtcIntersect1(scene.getRootScene(), &intersectContext, RTCRayHit_(ray));

    if (ray.geomID == RTC_INVALID_GEOMETRY_ID)
    {
        // TODO: Hardcoded sky value for now.
        return Vector3(0.7, 0.8, 0.9);
    }

    // We return a color based on the "instID" of the intersected geometry.
    // In Embree, the "primID" correspond to a unique *piece* of geometry, such as a triangle,
    // the "geomID" correspond to a unique ID associated to a geometry we are tracing against in a given scene,
    // and the "instID" is the same as the "geomID", but for instances.
    // In the case of Tracer, as we adopted the "everything is an instance" philosophy, we are using
    // the "instID" instead of the "geomID", as the root/top-level scene we are tracing against contains only instances,
    // and no actual geometry prototypes.
    return Vector3((static_cast<float>((ray.instID & 0x000000ff) >>  0)) / 255.0f,
        (static_cast<float>((ray.instID & 0x0000ff00) >>  8)) / 255.0f,
        (static_cast<float>((ray.instID & 0x00ff0000) >> 16)) / 255.0f);
}