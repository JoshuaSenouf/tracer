#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <embree3/common/math/vec3.h>

#include "object/ray.h"
#include "scene/scenemanager.h"
#include "utility/render_helper.h"


class Integrator
{
    public:
        Integrator();

        virtual embree::Vec3f GetPixelColor(
            Ray &ray,
            PixelSample &pixel_sample,
            SceneManager &scene_manager,
            const RenderGlobals &globals) = 0;
        virtual ShadingPoint SetupShadingPoint(
            SceneManager &scene_manager,
            const Ray &ray);
};

#endif // INTEGRATOR_H
