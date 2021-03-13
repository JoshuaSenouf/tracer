#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "integrator/debug.h"


DebugIntegrator::DebugIntegrator()
{
}

embree::Vec3f DebugIntegrator::GetPixelColor(
    Ray &ray,
    PixelSample &pixel_sample,
    SceneManager &scene_manager,
    const RenderGlobals &globals)
{
    RTCIntersectContext intersect_context;

    rtcInitIntersectContext(&intersect_context);
    rtcIntersect1(scene_manager.scene, &intersect_context, RTCRayHit_(ray));

    if (ray.inst_id == RTC_INVALID_GEOMETRY_ID)
    {
        // TODO: Hardcoded sky color value for now.
        return embree::Vec3f(0.7, 0.8, 0.9);
    }

    // We setup all the necessary data describing the shading point.
    ShadingPoint shading_point(SetupShadingPoint(scene_manager, ray));

    // We return a color based on the "inst_id" of the intersected geometry.
    // In Embree, the "prim_id" correspond to a unique *piece* of geometry, such as a triangle,
    // the "geom_id" correspond to a unique ID associated to a geometry we are tracing against in a given scene,
    // and the "inst_id" is the same as the "geom_id", but for instances.
    // In the case of Tracer, as we adopted the "everything is an instance" philosophy, we are using
    // the "inst_id" instead of the "geom_id", as the root/top-level scene we are tracing against contains only instances,
    // and no actual geometry prototypes.
    // TODO: Using a "parallel_for_each" loop in the SceneManager to generate the Embree geometry
    // means that the IDs will never be the same everytime we run Tracer.
    return embree::Vec3f(
        (static_cast<float>((shading_point.inst_id & 0x000000ff) >>  0)) / 255.0f,
        (static_cast<float>((shading_point.inst_id & 0x0000ff00) >>  8)) / 255.0f,
        (static_cast<float>((shading_point.inst_id & 0x00ff0000) >> 16)) / 255.0f);
}
