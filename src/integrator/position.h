#ifndef POSITION_H
#define POSITION_H

#include "integrator.h"


struct PositionIntegrator : public Integrator
{
    PositionIntegrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) override;
};

#endif // POSITION_H
