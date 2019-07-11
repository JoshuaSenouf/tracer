#ifndef NORMAL_H
#define NORMAL_H

#include "integrator.h"


struct NormalIntegrator : public Integrator
{
    NormalIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        Sample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) override;
};

#endif // NORMAL_H
