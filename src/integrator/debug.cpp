#include "debug.h"

#include "render_helper.h"


DebugIntegrator::DebugIntegrator()
{
    handle = "Debug";
}

embree::Vec3f DebugIntegrator::getPixelColor(Ray& ray,
    SceneManager &sceneManager,
    Randomizer& randEngine,
    int rayDepth)
{
    RTCIntersectContext intersectContext;
    rtcInitIntersectContext(&intersectContext);

    rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

    if (ray.geomID == RTC_INVALID_GEOMETRY_ID)
    {
        // TODO: Hardcoded sky value for now.
        return embree::Vec3f(0.7, 0.8, 0.9);
    }

    // Creating a local copy of the Geometry pointer here will
    // decrease performance a bit, for obvious reasons, the solution being
    // to only reference the one from the geometry map from the SceneManager.
    // auto intersectedGeomPtr(sceneManager._sceneGeom[ray.instID]);

    // We return a color based on the "instID" of the intersected geometry.
    // In Embree, the "primID" correspond to a unique *piece* of geometry, such as a triangle,
    // the "geomID" correspond to a unique ID associated to a geometry we are tracing against in a given sceneManager,
    // and the "instID" is the same as the "geomID", but for instances.
    // In the case of Tracer, as we adopted the "everything is an instance" philosophy, we are using
    // the "instID" instead of the "geomID", as the root/top-level scene we are tracing against contains only instances,
    // and no actual geometry prototypes.
    // TODO: Using a "parallel_for_each" loop in the SceneManager to generate the Embree geometry
    // means that the IDs will never be the same everytime we run Tracer.
    return embree::Vec3f((static_cast<float>((ray.instID & 0x000000ff) >>  0)) / 255.0f,
        (static_cast<float>((ray.instID & 0x0000ff00) >>  8)) / 255.0f,
        (static_cast<float>((ray.instID & 0x00ff0000) >> 16)) / 255.0f);
}