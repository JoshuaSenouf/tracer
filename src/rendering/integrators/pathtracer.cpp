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
        float closestSphereDist;
        int closestSphereID = 0;

        if (!renderScene.isIntersected(cameraRay, closestSphereDist, closestSphereID))
            return colorAccumulation += colorMask * renderScene.getSettings().skyColor; // If we hit no object, we return the sky color

        Sphere hitSphere = renderScene.getSphereList()[closestSphereID];

        if (hitSphere.getMaterial().getEmissiveColor() != Vector3())
            return colorAccumulation += colorMask * hitSphere.getMaterial().getEmissiveColor(); // If we hit a light source, how about stopping earlier ?

        cameraRay.getOrigin() += cameraRay.getDirection() * closestSphereDist;
        const Vector3 hitNormal = (cameraRay.getOrigin() - hitSphere.getPosition()).normalize();

        bsdfSampling = hitSphere.getMaterial().computeSampling(cameraRay.getDirection(), hitNormal, randEngine);

        colorMask *= bsdfSampling;
    }

    return colorAccumulation;
}
