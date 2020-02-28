#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "integrator.h"


struct OcclusionIntegrator : public Integrator
{
    OcclusionIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& sample,
        SceneManager &scene,
        const RenderGlobals& globals) override;
};

#endif // OCCLUSION_H
