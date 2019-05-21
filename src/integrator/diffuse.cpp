#include "diffuse.h"


DiffuseIntegrator::DiffuseIntegrator()
{
    handle = "Diffuse";
}

Vector3 DiffuseIntegrator::getPixelColor(Ray& ray,
    SceneManager &scene,
    Randomizer& randEngine,
    int rayDepth)
{
    // TODO

    return Vector3(0.0f);
}