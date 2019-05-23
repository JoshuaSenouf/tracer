#include "occlusion.h"


OcclusionIntegrator::OcclusionIntegrator()
{
    handle = "Occlusion";
}

embree::Vec3f OcclusionIntegrator::getPixelColor(Ray& ray,
    SceneManager &sceneManager,
    Randomizer& randEngine,
    int rayDepth)
{
    // TODO

    return embree::Vec3f(0.0f);
}