#ifndef DEBUG_H
#define DEBUG_H

#include "integrator.h"


struct DebugIntegrator : public Integrator
{
    DebugIntegrator();

    virtual Vector3 getPixelColor(Ray& ray,
        SceneManager &scene,
        Randomizer& randEngine,
        int rayDepth) override;
};

#endif // DEBUG_H
