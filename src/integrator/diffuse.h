#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "integrator.h"


struct DiffuseIntegrator : public Integrator
{
    DiffuseIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) override;
};

#endif // DIFFUSE_H
