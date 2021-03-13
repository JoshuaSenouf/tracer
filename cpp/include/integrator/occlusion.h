#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "integrator/integrator.h"


class OcclusionIntegrator : public Integrator
{
    public:
        OcclusionIntegrator();

        virtual embree::Vec3f GetPixelColor(
            Ray &ray,
            PixelSample &pixel_sample,
            SceneManager &scene_manager,
            const RenderGlobals &globals) override;
};

#endif // OCCLUSION_H
