#ifndef NORMAL_H
#define NORMAL_H

#include "integrator.h"


struct NormalIntegrator : public Integrator
{
    NormalIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& sample,
        SceneManager &scene,
        const RenderGlobals& globals) override;
};

#endif // NORMAL_H
