#include "integrator.h"


Integrator::Integrator()
{
}

ShadingPoint Integrator::SetupShadingPoint(SceneManager &scene,
    const Ray& ray)
{
    ShadingPoint shadingPoint(scene._sceneGeom[ray.instID]);

    shadingPoint.V = -ray.direction;
    shadingPoint.P = ray.origin + ray.tfar * ray.direction;

    // TODO: Use the normals primvar if available (for smooth normals).
    shadingPoint.N = embree::normalize(ray.Ng);

    // Object to world space normal conversion.
    embree::Vec3f normalWorld(USDToEmbreeMatrixMultiply(shadingPoint.N, shadingPoint.geometry->_transform));
    // We make the normal faceforwarding.
    shadingPoint.Nw = embree::normalize(embree::dot(shadingPoint.V, normalWorld) < 0.0f ? -normalWorld : normalWorld);
    shadingPoint.UV = embree::Vec2fa(ray.u, ray.v);

    // We compute the tangent and bitangent from the normal.
    // TODO: Use the tangents primvar if available (for smooth tangents).
    embree::Vec3f tangent(0.0f);
    embree::Vec3f bitangent(0.0f);

    if(embree::abs(shadingPoint.Nw.x) > embree::abs(shadingPoint.Nw.y))
        tangent = embree::Vec3f(-shadingPoint.Nw.z, 0.0f, shadingPoint.Nw.x) *
            (1.0f / embree::sqrt(shadingPoint.Nw.x * shadingPoint.Nw.x +
                shadingPoint.Nw.y * shadingPoint.Nw.y +
                shadingPoint.Nw.z * shadingPoint.Nw.z));
    else
        tangent = embree::Vec3f(0.0f, shadingPoint.Nw.z, -shadingPoint.Nw.y) *
            (1.0f / embree::sqrt(shadingPoint.Nw.x * shadingPoint.Nw.x +
                shadingPoint.Nw.y * shadingPoint.Nw.y +
                shadingPoint.Nw.z * shadingPoint.Nw.z));

    bitangent = embree::normalize(embree::cross(shadingPoint.Nw, tangent));

    // We setup an orthogonal basis out of the normal, tangent and bitangent.
    shadingPoint.basis = pxr::GfMatrix3f(tangent.x, tangent.y, tangent.z,
        shadingPoint.Nw.x, shadingPoint.Nw.y, shadingPoint.Nw.z,
        bitangent.x, bitangent.y, bitangent.z);

    // We setup the last miscellaneous data of the shading point.
    shadingPoint.geomID = ray.geomID;
    shadingPoint.primID = ray.primID;
    shadingPoint.instID = ray.instID;
    shadingPoint.error = errorBias * std::max(
        std::max(std::abs(shadingPoint.P.x), abs(shadingPoint.P.y)), 
        std::max(std::abs(shadingPoint.P.z), ray.tfar));

    return shadingPoint;
}