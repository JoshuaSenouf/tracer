#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "occlusion.h"


OcclusionIntegrator::OcclusionIntegrator()
{
    _handle = "occlusion";
}

embree::Vec3f OcclusionIntegrator::GetPixelColor(Ray& ray,
    PixelSample& sample,
    SceneManager &scene,
    const RenderGlobals& globals)
{
    // TODO

    return embree::Vec3f(1.0f);
}
