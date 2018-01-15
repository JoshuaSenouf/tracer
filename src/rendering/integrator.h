#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "vector.h"
#include "randomizer.h"
#include "ray.h"
#include "sphere.h"
#include "scene.h"


class PathTracer
{
    public:
        PathTracer();

        Vector3 getRadiance(Ray& cameraRay, Scene& renderScene, Randomizer& randEngine, int rayDepth);

    private:

};


#endif // INTEGRATOR_H
