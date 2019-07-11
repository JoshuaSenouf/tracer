#include "diffuse.h"
#include "quadmesh.h"


DiffuseIntegrator::DiffuseIntegrator()
{
    _handle = "Diffuse";
}

embree::Vec3f DiffuseIntegrator::GetPixelColor(Ray& ray,
    Sample& pixelSample,
    SceneManager &sceneManager,
    const RenderGlobals& renderGlobals)
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
    embree::Vec3f normalObject(ray.Ng);
    // Object to world space normal conversion.
    embree::Vec3f normalWorld(normalObject.x * transform[0][0] +
            normalObject.y * transform[1][0] +
            normalObject.z * transform[2][0],
        normalObject.x * transform[0][1] +
            normalObject.y * transform[1][1] +
            normalObject.z * transform[2][1],
        normalObject.x * transform[0][2] +
            normalObject.y * transform[1][2] +
            normalObject.z * transform[2][2]);

    normalWorld = embree::normalize(embree::dot(ray.direction, normalWorld) < 0.0f ? normalWorld : -normalWorld);

    ShadingPoint shadingPoint(position,
        normalObject,
        normalWorld,
        embree::Vec2fa(ray.u, ray.v),
        -ray.direction,
        ray.geomID,
        ray.primID,
        ray.instID);

    float diffuse(std::fabs(embree::dot(shadingPoint.Nw, ray.direction)));

    return embree::Vec3f(intersectedGeom->_displayColor * diffuse * (1.0f / M_PI));
}
