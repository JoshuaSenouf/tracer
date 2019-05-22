#ifndef UPDT_H
#define UPDT_H

#include "integrator.h"


struct UDPTIntegrator : public Integrator
{
    UDPTIntegrator();

    virtual embree::Vec3f getPixelColor(Ray& ray,
        SceneManager &scene,
        Randomizer& randEngine,
        int rayDepth);
};

#endif // UPDT_H
