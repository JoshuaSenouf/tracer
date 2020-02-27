#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <embree3/common/math/vec3.h>

#include "ray.h"
#include "render_helper.h"
#include "scenemanager.h"


struct Integrator
{
    Integrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& sample,
        SceneManager &scene,
        const RenderGlobals& globals) = 0;
    virtual ShadingPoint SetupShadingPoint(SceneManager &scene,
        const Ray& ray);

    std::string _handle;
};

#endif // INTEGRATOR_H
