#ifndef PATHTRACER_H
#define PATHTRACER_H

#include "vector.h"
#include "randomizer.h"
#include "ray.h"
#include "scenemanager.h"
#include "embree_helper.h"
#include "material.h"


class PathTracer
{
    public:
        PathTracer();

        Vector3 getRadiance(Ray& cameraRay,
            SceneManager& renderScene,
            Randomizer& randEngine,
            int rayDepth);

    private:
        BSDF testMaterial;

};


#endif // PATHTRACER_H
