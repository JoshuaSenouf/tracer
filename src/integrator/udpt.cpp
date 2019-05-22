#include "udpt.h"


UDPTIntegrator::UDPTIntegrator()
{
    handle = "UDPT";
}

embree::Vec3f UDPTIntegrator::getPixelColor(Ray& ray,
    SceneManager &scene,
    Randomizer& randEngine,
    int rayDepth)
{
    // TODO

    return embree::Vec3f(0.0f);
}