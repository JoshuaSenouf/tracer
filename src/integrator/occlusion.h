#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "integrator.h"


struct OcclusionIntegrator : public Integrator
{
    OcclusionIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) override;
};

#endif // OCCLUSION_H
