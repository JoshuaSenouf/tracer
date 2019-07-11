#include "occlusion.h"


OcclusionIntegrator::OcclusionIntegrator()
{
    _handle = "Occlusion";
}

embree::Vec3f OcclusionIntegrator::GetPixelColor(Ray& ray,
    Sample& pixelSample,
    SceneManager &sceneManager,
    const RenderGlobals& renderGlobals)
{
    // TODO

    return embree::Vec3f(1.0f);
}
