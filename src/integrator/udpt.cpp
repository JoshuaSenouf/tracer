#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "integrator/udpt.h"


UDPTIntegrator::UDPTIntegrator()
{
}

embree::Vec3f UDPTIntegrator::GetPixelColor(
    Ray &ray,
    PixelSample &pixel_sample,
    SceneManager &scene_manager,
    const RenderGlobals &globals)
{
    embree::Vec3f color_accumulation(0.0f);
    embree::Vec3f color_throughput(1.0f);

    for (int bounce = 0; bounce < globals.depth; ++bounce)
    {
        RTCIntersectContext intersect_context;

        rtcInitIntersectContext(&intersect_context);
        rtcIntersect1(scene_manager.scene, &intersect_context, RTCRayHit_(ray));

        if (ray.inst_id == RTC_INVALID_GEOMETRY_ID)
        {
            // TODO: Hardcoded sky color value for now.
            return color_accumulation += color_throughput * embree::Vec3f(0.7, 0.8, 0.9);
        }

        // We setup all the necessary data describing the shading point.
        ShadingPoint shading_point(SetupShadingPoint(scene_manager, ray));

        // Sky/Environment Sampling
        // TODO

        // Light Sampling/Next Event Estimation
        // TODO

        // BSDF Sampling
        BSDFSample bsdf_sample;
        // TODO: We should use a proper material instead of a BSDF/Lobe directly.
        bsdf_sample.wi = diffuse_mat.Sample(pixel_sample, shading_point, bsdf_sample);
        bsdf_sample.reflectance = diffuse_mat.Evaluate(pixel_sample, shading_point, bsdf_sample);

        // Using the world-space normal and the error bias of the shading point , as well as a sign,
        // we apply some form of jitter on the position of the shading point,
        // effectively offsetting the origin of the following ray.
        float direction_sign(embree::sign(embree::dot(bsdf_sample.wi, shading_point.Nw)));
        ray.origin = shading_point.P + (direction_sign * shading_point.error * shading_point.Nw);
        ray.direction = bsdf_sample.wi;

        // Initializing the new ray.
        ray = Ray(ray.origin, ray.direction, shading_point.error);

        color_throughput = color_throughput * (bsdf_sample.reflectance / bsdf_sample.pdf);
    }

    return color_accumulation;
}
