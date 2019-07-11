#ifndef DEBUG_H
#define DEBUG_H

#include "integrator.h"


struct DebugIntegrator : public Integrator
{
    DebugIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        Sample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) override;
};

#endif // DEBUG_H
