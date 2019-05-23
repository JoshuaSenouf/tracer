#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "ray.h"
#include "randomizer.h"
#include "scenemanager.h"
#include "embree_helper.h"


struct Integrator
{
    Integrator();

    virtual embree::Vec3f getPixelColor(Ray& ray,
        SceneManager &sceneManager,
        Randomizer& randEngine,
        int rayDepth) = 0;

    std::string handle;
};

#endif // INTEGRATOR_H
