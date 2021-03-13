#ifndef NORMAL_H
#define NORMAL_H

#include "integrator/integrator.h"


class NormalIntegrator : public Integrator
{
    public:
        NormalIntegrator();

        virtual embree::Vec3f GetPixelColor(
            Ray &ray,
            PixelSample &pixel_sample,
            SceneManager &scene_manager,
            const RenderGlobals &globals) override;
};

#endif // NORMAL_H
