#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "integrator/occlusion.h"


OcclusionIntegrator::OcclusionIntegrator()
{
}

embree::Vec3f OcclusionIntegrator::GetPixelColor(
    Ray &ray,
    PixelSample &pixel_sample,
    SceneManager &scene_manager,
    const RenderGlobals &globals)
{
    // TODO

    return embree::Vec3f(1.0f);
}
