#include "diffuse.h"


DiffuseIntegrator::DiffuseIntegrator()
{
    handle = "Diffuse";
}

embree::Vec3f DiffuseIntegrator::getPixelColor(Ray& ray,
    SceneManager &scene,
    Randomizer& randEngine,
    int rayDepth)
{
    // TODO

    return embree::Vec3f(0.0f);
}