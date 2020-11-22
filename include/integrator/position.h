#ifndef POSITION_H
#define POSITION_H

#include "integrator/integrator.h"


class PositionIntegrator : public Integrator
{
    public:
        PositionIntegrator();

        virtual embree::Vec3f GetPixelColor(
            Ray &ray,
            PixelSample &pixel_sample,
            SceneManager &scene_manager,
            const RenderGlobals &globals) override;
};

#endif // POSITION_H
