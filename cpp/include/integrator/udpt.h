#ifndef UPDT_H
#define UPDT_H

#include "bsdf/lambert.h"

#include "integrator/integrator.h"


class UDPTIntegrator : public Integrator
{
    public:
        UDPTIntegrator();

        virtual embree::Vec3f GetPixelColor(
            Ray &ray,
            PixelSample &pixel_sample,
            SceneManager &scene_manager,
            const RenderGlobals &globals) override;

    private:
        // TODO: To remove once we have a proper material system.
        Lambert diffuse_mat;
};

#endif // UPDT_H
