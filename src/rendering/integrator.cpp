#include "integrator.h"


PathTracer::PathTracer()
{

}


Vector3 PathTracer::getRadiance(Ray& cameraRay, Scene& renderScene, Randomizer& randEngine, int rayDepth)
{
    Vector3 colorAccumulation;
    Vector3 colorMask(1.0f, 1.0f, 1.0f);

    for (int bounces = 0; bounces < rayDepth; ++bounces)
    {
        float closestSphereDist;
        int closestSphereID = 0;

        if (!renderScene.isIntersected(cameraRay, closestSphereDist, closestSphereID))
            return colorAccumulation += colorMask * Vector3(0.7f, 0.8f, 0.8f); // If we hit no object, we return the sky color

        const Sphere &hitSphere = renderScene.getSpheresList()[closestSphereID];
        Vector3 hitCoord = cameraRay.origin + cameraRay.direction * closestSphereDist;
        Vector3 hitNormal = (hitCoord - hitSphere.position).normalize();
        Vector3 hitOrientedNormal = hitNormal.dot(cameraRay.direction) < 0.0f ? hitNormal : hitNormal * -1.0f;

        colorAccumulation += colorMask * hitSphere.material.emissiveColor;

        colorMask *= hitSphere.material.color;

        Vector3 nextRayDir;
        Vector3 bsdfSampling;

        cameraRay.direction = nextRayDir;
        cameraRay.origin = hitCoord;
    }

    return colorAccumulation;
}
