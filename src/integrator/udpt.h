#ifndef UPDT_H
#define UPDT_H

#include "integrator.h"
#include "material.h"


struct UDPTIntegrator : public Integrator
{
    UDPTIntegrator();

    virtual embree::Vec3f getPixelColor(Ray& ray,
        SceneManager &sceneManager,
        Randomizer& randEngine,
        int rayDepth);
};

#endif // UPDT_H
