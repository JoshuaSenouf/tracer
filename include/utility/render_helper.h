#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>

#include <pxr/base/gf/matrix3f.h>

#include "object/geometry.h"
#include "sampling/sampler.h"


// From Embree 3.x
static const float error_bias = 32.0f * 1.19209e-07f;

enum IntegratorIDs {
    kUDPT = 0,
    kDiffuse,
    kOcclusion,
    kPosition,
    kNormal,
    kDebug,
};

struct RenderGlobals
{
    // The width of the image to render.
    int width = 800;
    // The height of the image to render.
    int height = 600;
    // The maximum ray depth, or number of bounces, the renderer can make use of.
    int depth = 3;
    // Total number of samples per pixel to compute.
    int samples = 1;
    // The ID of the integrator currently being used by the renderer.
    int integrator_id = kUDPT;
    // Define whether the camera rays should be jittered or not.
    bool jitter_rays = true;
};

struct PixelSample
{
    // Position of the pixel being sampled on the X-axis.
    int pixel_x = 0;
    // Position of the pixel being sampled on the Y-axis.
    int pixel_y = 0;
    // Index of the pixel being sampled, from 0 to (width * height).
    int pixel_idx = 0;
    // Total number of samples per pixel to compute.
    int samples = 0;
    // Keep track of how many samples have been computed.
    int sample_idx = 0;
    // Sampler to use to generate any random numbers in this sample.
    Sampler &sampler;

    __forceinline PixelSample(
        Sampler &sampler)
        : sampler(sampler)
    {
    }
};

struct BSDFSample
{
    // Reflectance of the BSDF sample.
    embree::Vec3f reflectance = embree::Vec3f(0.0f);
    // Direction of the BSDF sample.
    embree::Vec3f wi = embree::Vec3fa(0.0f);
    // Dot product of the world-space normal and the exitant/light direction.
    float NdotL = 0.0f;
    // Dot product of the world-space normal and the incident/view direction.
    float NdotV = 0.0f;
    // PDF of the BSDF sample.
    float pdf = 0.0f;
};

struct ShadingPoint
{
    // Geometry that was intersected by the ray.
    const std::shared_ptr<Geometry> &geom;
    // View vector of the ray.
    embree::Vec3fa V = embree::Vec3fa(0.0f);
    // World-space position of the shading point.
    embree::Vec3fa P = embree::Vec3fa(0.0f);
    // Object/Local-space normal of the shading point.
    embree::Vec3f N = embree::Vec3f(0.0f);
    // World-space normal of the shading point.
    embree::Vec3f Nw = embree::Vec3f(0.0f);
    // UV barycentric coordinates of the shading point.
    embree::Vec2fa UV = embree::Vec2fa(0.0f);
    // Orthogonal basis of the shading point used for shading computation.
    pxr::GfMatrix3f basis = pxr::GfMatrix3f(1.0f);
    // Embree Geometry ID of the object the ray hit.
    unsigned int geom_id = RTC_INVALID_GEOMETRY_ID;
    // Embree Primitive ID of the object the ray hit.
    unsigned int prim_id = RTC_INVALID_GEOMETRY_ID;
    // Embree Instance ID of the object the ray hit.
    unsigned int inst_id = RTC_INVALID_GEOMETRY_ID;
    // Error to take into account when intersecting a primitive.
    float error = 0.0f;

    __forceinline ShadingPoint(
        const std::shared_ptr<Geometry> &geom)
        : geom(geom)
    {
    }
};

// GLfloat
static const float screen_quad_vertices[] =
{
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

#endif // RENDER_HELPER_H
