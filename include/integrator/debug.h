#ifndef DEBUG_H
#define DEBUG_H

#include "integrator.h"


struct DebugIntegrator : public Integrator
{
    DebugIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& sample,
        SceneManager &scene,
        const RenderGlobals& globals) override;
};

#endif // DEBUG_H
