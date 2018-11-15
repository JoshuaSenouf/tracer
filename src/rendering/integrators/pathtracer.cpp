#include "pathtracer.h"


PathTracer::PathTracer()
{

}


Vector3 PathTracer::getRadiance(Ray& cameraRay,
    SceneManager &renderScene,
    Randomizer& randEngine,
    int rayDepth)
{
    Vector3 bsdfSampling;
    Vector3 colorAccumulation;
    Vector3 colorMask(1.0f, 1.0f, 1.0f);

    for (int bounces = 0; bounces < rayDepth; ++bounces)
    {
        bool isLightSource = false;
        float closestGeoDist;
        int closestGeoID = 0;

        // if (!renderScene.isIntersected(cameraRay, closestGeoDist, closestGeoID, isLightSource))
        //     return colorAccumulation += colorMask * renderScene.getSettings().skyColor; // If we hit no object, we return the sky color

        // if(isLightSource)
        // {
        //     return colorAccumulation += colorMask *
        //         renderScene.getLightList()[closestGeoID].getMaterial().getEmissiveColor();
        // }

        // Sphere hitGeo = renderScene.getSphereList()[closestGeoID];

        // cameraRay.getOrigin() += cameraRay.getDirection() * closestGeoDist;
        // const Vector3 hitNormal = (cameraRay.getOrigin() - hitGeo.getPosition()).normalize();

        // bsdfSampling = hitGeo.getMaterial().computeSampling(cameraRay.getDirection(), hitNormal, randEngine);

        // colorMask *= bsdfSampling;
    }

    return colorAccumulation;
}
