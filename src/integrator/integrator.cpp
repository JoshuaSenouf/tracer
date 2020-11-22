#include <embree3/common/math/vec2.h>

#include <pxr/base/gf/matrix3f.h>

#include "utility/math_helper.h"

#include "integrator/integrator.h"


Integrator::Integrator()
{
}

ShadingPoint Integrator::SetupShadingPoint(
    SceneManager &scene_manager,
    const Ray &ray)
{
    ShadingPoint shading_point(scene_manager.scene_geom[ray.inst_id]);

    shading_point.V = -ray.direction;
    shading_point.P = ray.origin + ray.t_far * ray.direction;

    // TODO: Use the normals primvar if available (for smooth normals).
    shading_point.N = embree::normalize(ray.Ng);

    // Object to world space normal conversion.
    embree::Vec3f normal_world(USDToEmbreeMatrixMultiply(shading_point.N, shading_point.geom->transform));
    // We make the normal faceforwarding.
    shading_point.Nw = embree::normalize(
        embree::dot(shading_point.V, normal_world) < 0.0f ? -normal_world : normal_world);
    shading_point.UV = embree::Vec2fa(ray.u, ray.v);

    // We compute the tangent and bitangent from the normal.
    // TODO: Use the tangents primvar if available (for smooth tangents).
    embree::Vec3f tangent(0.0f);
    embree::Vec3f bitangent(0.0f);

    if(embree::abs(shading_point.Nw.x) > embree::abs(shading_point.Nw.y))
        tangent = embree::Vec3f(-shading_point.Nw.z, 0.0f, shading_point.Nw.x) *
            (1.0f / embree::sqrt(shading_point.Nw.x * shading_point.Nw.x +
                shading_point.Nw.y * shading_point.Nw.y +
                shading_point.Nw.z * shading_point.Nw.z));
    else
        tangent = embree::Vec3f(0.0f, shading_point.Nw.z, -shading_point.Nw.y) *
            (1.0f / embree::sqrt(shading_point.Nw.x * shading_point.Nw.x +
                shading_point.Nw.y * shading_point.Nw.y +
                shading_point.Nw.z * shading_point.Nw.z));

    bitangent = embree::normalize(embree::cross(shading_point.Nw, tangent));

    // We setup an orthogonal basis out of the normal, tangent and bitangent.
    shading_point.basis = pxr::GfMatrix3f(tangent.x, tangent.y, tangent.z,
        shading_point.Nw.x, shading_point.Nw.y, shading_point.Nw.z,
        bitangent.x, bitangent.y, bitangent.z);

    // We setup the last miscellaneous data of the shading point.
    shading_point.geom_id = ray.geom_id;
    shading_point.prim_id = ray.prim_id;
    shading_point.inst_id = ray.inst_id;
    shading_point.error = error_bias * std::max(
        std::max(std::abs(shading_point.P.x), abs(shading_point.P.y)),
        std::max(std::abs(shading_point.P.z), ray.t_far));

    return shading_point;
}