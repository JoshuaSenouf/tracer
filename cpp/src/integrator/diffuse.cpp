#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "integrator/diffuse.h"


DiffuseIntegrator::DiffuseIntegrator()
{
}

embree::Vec3f DiffuseIntegrator::GetPixelColor(
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

    float diffuse_factor(std::fabs(embree::dot(shading_point.Nw, ray.direction)));

    return embree::Vec3f(shading_point.geom->display_color * diffuse_factor * (1.0f / M_PI));
}
