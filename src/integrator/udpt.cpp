#include "udpt.h"


UDPTIntegrator::UDPTIntegrator()
{
    handle = "UDPT";
}

embree::Vec3f UDPTIntegrator::getPixelColor(Ray& ray,
    SceneManager &sceneManager,
    Randomizer& randEngine,
    int rayDepth)
{
    for (int bounces = 0; bounces < rayDepth; ++bounces)
    {
        RTCIntersectContext intersectContext;
        rtcInitIntersectContext(&intersectContext);

        rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

        if (ray.geomID == RTC_INVALID_GEOMETRY_ID)
        {
            // TODO: Hardcoded sky color value for now.
            return embree::Vec3f(0.7, 0.8, 0.9);
        }

        embree::Vec3f position(ray.origin + ray.tfar * ray.direction);
        embree::Vec3f normal(embree::normalize(ray.Ng));

        // TODO
    }

    return embree::Vec3f(0.0f);
}