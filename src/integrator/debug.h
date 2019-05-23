#ifndef DEBUG_H
#define DEBUG_H

#include "integrator.h"


struct DebugIntegrator : public Integrator
{
    DebugIntegrator();

    virtual embree::Vec3f getPixelColor(Ray& ray,
        SceneManager &sceneManager,
        Randomizer& randEngine,
        int rayDepth) override;
};

#endif // DEBUG_H
