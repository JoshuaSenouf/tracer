#include "integrator.h"


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

        if (hitSphere.material.emissiveColor != Vector3())
            return colorAccumulation += colorMask * hitSphere.material.emissiveColor; // If we hit a light source, how about stopping earlier ?

        cameraRay.origin += cameraRay.direction * closestSphereDist;
        const Vector3 hitNormal = (cameraRay.origin - hitSphere.position).normalize();

        bsdfSampling = hitSphere.material.computeSampling(cameraRay.direction, hitNormal, randEngine);

        colorMask *= bsdfSampling;
    }

    return colorAccumulation;
}
