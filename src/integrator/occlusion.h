#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "integrator.h"


struct OcclusionIntegrator : public Integrator
{
    OcclusionIntegrator();

    virtual embree::Vec3f getPixelColor(Ray& ray,
        SceneManager &sceneManager,
        Randomizer& randEngine,
        int rayDepth);
};

#endif // OCCLUSION_H
