#ifndef DEBUG_H
#define DEBUG_H

#include "integrator/integrator.h"


class DebugIntegrator : public Integrator
{
    public:
        DebugIntegrator();

        virtual embree::Vec3f GetPixelColor(
            Ray &ray,
            PixelSample &pixel_sample,
            SceneManager &scene_manager,
            const RenderGlobals &globals) override;
};

#endif // DEBUG_H
