#include "diffuse.h"
#include "quadmesh.h"


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
        // TODO: Hardcoded sky color value for now.
        return embree::Vec3f(0.7, 0.8, 0.9);
    }

    auto intersectedGeom(sceneManager._sceneGeom[ray.instID].get());

    pxr::GfMatrix4f transform(intersectedGeom->_transform);
    embree::Vec3f position(ray.origin + ray.tfar * ray.direction);
    // TODO: Use the normals primvar if available (for smooth normals).
    embree::Vec3f normalObject(embree::normalize(ray.Ng));
    // Object to world space normal conversion.
    embree::Vec3f normalWorld(normalObject[0] * transform[0][0] +
            normalObject[1] * transform[1][0] +
            normalObject[2] * transform[2][0],
        normalObject[0] * transform[0][1] +
            normalObject[1] * transform[1][1] +
            normalObject[2] * transform[2][1],
        normalObject[0] * transform[0][2] +
            normalObject[1] * transform[1][2] +
            normalObject[2] * transform[2][2]);

    float diffuseComponent(std::fabs(embree::dot(normalWorld, ray.direction)));

    return embree::Vec3f(intersectedGeom->_color * diffuseComponent);
}