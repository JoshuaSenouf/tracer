#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "integrator.h"


struct DiffuseIntegrator : public Integrator
{
    DiffuseIntegrator();

    virtual Vector3 getPixelColor(Ray& ray,
        SceneManager &scene,
        Randomizer& randEngine,
        int rayDepth);
};

#endif // DIFFUSE_H
