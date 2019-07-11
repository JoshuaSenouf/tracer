#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "material.h"
#include "ray.h"
#include "sampler.h"
#include "scenemanager.h"

#include "embree_helper.h"
#include "render_helper.h"


struct Integrator
{
    Integrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        Sample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) = 0;

    std::string _handle;
};

#endif // INTEGRATOR_H
