#ifndef UPDT_H
#define UPDT_H

#include "integrator.h"


struct UDPTIntegrator : public Integrator
{
    UDPTIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        Sample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) override;
};

#endif // UPDT_H
