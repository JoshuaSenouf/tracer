#ifndef UPDT_H
#define UPDT_H

#include "integrator.h"


#include "lambert.h"
#include "orennayar.h"


struct UDPTIntegrator : public Integrator
{
    UDPTIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& sample,
        SceneManager &scene,
        const RenderGlobals& globals) override;

    // TODO: To remove once we have a proper material system.
    Lambert diffuseMat;
};

#endif // UPDT_H
