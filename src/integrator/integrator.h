#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "vector.h"
#include "ray.h"
#include "randomizer.h"
#include "scenemanager.h"


struct Integrator
{
    Integrator();

    virtual Vector3 getPixelColor(Ray& ray,
        SceneManager &scene,
        Randomizer& randEngine,
        int rayDepth) = 0;

    std::string handle;
};

#endif // INTEGRATOR_H
