#include "diffuse.h"


DiffuseIntegrator::DiffuseIntegrator()
{
    handle = "Diffuse";
}

embree::Vec3f DiffuseIntegrator::getPixelColor(Ray& ray,
    SceneManager &sceneManager,
    Randomizer& randEngine,
    int rayDepth)
{
    RTCIntersectContext intersectContext;
    rtcInitIntersectContext(&intersectContext);

    rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

    if (ray.geomID == RTC_INVALID_GEOMETRY_ID)
    {
        // TODO: Hardcoded sky value for now.
        return embree::Vec3f(0.7, 0.8, 0.9);
    }

    embree::Vec3f position(ray.origin + ray.tfar * ray.direction);
    // TODO: Use the normals primvar if available (for smooth normals).
    embree::Vec3f normal(embree::normalize(ray.Ng));
    // TODO: Use the displayColor primvar if available when the material system will be ready.
    embree::Vec3f color(0.5f);

    float diffuseComponent = std::fabs(embree::dot(ray.direction, normal));

    return embree::Vec3f((color * M_1_PI) * diffuseComponent);
}