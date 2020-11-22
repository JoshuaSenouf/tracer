#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "integrator/integrator.h"


class DiffuseIntegrator : public Integrator
{
    public:
        DiffuseIntegrator();

        virtual embree::Vec3f GetPixelColor(
            Ray &ray,
            PixelSample &pixel_sample,
            SceneManager &scene_manager,
            const RenderGlobals &globals) override;
};

#endif // DIFFUSE_H
