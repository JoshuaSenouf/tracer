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
        RTCIntersectContext intersectContext;
        rtcInitIntersectContext(&intersectContext);

        rtcIntersect1(renderScene.getRootScene(), &intersectContext, RTCRayHit_(cameraRay));

        if (cameraRay.geomID == RTC_INVALID_GEOMETRY_ID)
        {
            // TODO: Hardcoded value for now.
            return colorAccumulation += colorMask * Vector3(0.7, 0.8, 0.9);
        }

        return Vector3(((float)((cameraRay.instID & 0x000000ff) >>  0)) / 255.0f,
            ((float)((cameraRay.instID & 0x0000ff00) >>  8)) / 255.0f,
            ((float)((cameraRay.instID & 0x00ff0000) >> 16)) / 255.0f);

        // return Vector3(randEngine.getRandomFloat());
    }

    return colorAccumulation;
}
