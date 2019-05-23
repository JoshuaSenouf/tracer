#ifndef NORMAL_H
#define NORMAL_H

#include "integrator.h"


struct NormalIntegrator : public Integrator
{
    NormalIntegrator();

    virtual embree::Vec3f getPixelColor(Ray& ray,
        SceneManager &sceneManager,
        Randomizer& randEngine,
        int rayDepth) override;
};

#endif // NORMAL_H
