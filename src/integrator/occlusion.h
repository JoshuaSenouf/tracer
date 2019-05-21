#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "integrator.h"


struct OcclusionIntegrator : public Integrator
{
    OcclusionIntegrator();

    virtual Vector3 getPixelColor(Ray& ray,
        SceneManager &scene,
        Randomizer& randEngine,
        int rayDepth);
};

#endif // OCCLUSION_H
