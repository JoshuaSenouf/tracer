#ifndef POSITION_H
#define POSITION_H

#include "integrator.h"


struct PositionIntegrator : public Integrator
{
    PositionIntegrator();

    virtual embree::Vec3f getPixelColor(Ray& ray,
        SceneManager &sceneManager,
        Randomizer& randEngine,
        int rayDepth) override;
};

#endif // POSITION_H
