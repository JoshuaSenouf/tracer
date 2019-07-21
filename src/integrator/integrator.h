#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "material.h"
#include "ray.h"
#include "sampler.h"
#include "scenemanager.h"

#include "embree_helper.h"
#include "math_helper.h"
#include "render_helper.h"


struct Integrator
{
    Integrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) = 0;
    virtual ShadingPoint SetupShadingPoint(SceneManager &sceneManager,
        const Ray& ray);

    std::string _handle;
};

#endif // INTEGRATOR_H
