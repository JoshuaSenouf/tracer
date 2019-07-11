#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include "glad/glad.h"

#include "sampler.h"

#include "embree_helper.h"


static const GLfloat screenQuadVertices[] =
{
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

enum INTEGRATOR_ID {
    UDPT,
    DIFFUSE,
    OCCLUSION,
    POSITION,
    NORMAL,
    DEBUG,
};

struct RenderGlobals
{
    int width;
    int height;
    int depth;
    int samples;
    int integratorID;
    bool rayJitter;

    RenderGlobals() {};

    __forceinline RenderGlobals(int width,
        int height,
        int depth,
        int samples,
        int integratorID,
        bool rayJitter)
        : width(width),
        height(height),
        depth(depth),
        samples(samples),
        integratorID(integratorID),
        rayJitter(rayJitter)
    {
    }
};

struct Sample
{
    int pixelX;
    int pixelY;
    int pixelIdx;
    int sampleIdx;
    int sampleCount;
    Sampler& sampler;

    __forceinline Sample(int pixelX,
        int pixelY,
        int pixelIdx,
        int sampleIdx,
        int sampleCount,
        Sampler& sampler)
        : pixelX(pixelX),
        pixelY(pixelY),
        pixelIdx(pixelIdx),
        sampleIdx(sampleIdx),
        sampleCount(sampleCount),
        sampler(sampler)
    {
    }
};

struct ShadingPoint
{
    // embree::Vec3f color;     // Shaded color of the shading point.
    const embree::Vec3fa& P;    // World-space position of the shading point.
    const embree::Vec3f& N;     // Object/Local-space normal of the shading point.
    const embree::Vec3f& Nw;    // World-space normal of the shading point.
    const embree::Vec2fa& UV;   // UV barycentric coordinates of the shading point.
    const embree::Vec3fa& V;    // View vector from the camera.
    const uint& geomID;         // Embree Geometry ID of the object the ray hit;
    const uint& primID;         // Embree Primitive ID of the object the ray hit;
    const uint& instID;         // Embree Instance ID of the object the ray hit;

    __forceinline ShadingPoint(const embree::Vec3fa& P = embree::Vec3fa(0.0f),
        const embree::Vec3f& N = embree::Vec3f(0.0f),
        const embree::Vec3f& Nw = embree::Vec3f(0.0f),
        const embree::Vec2fa& UV = embree::Vec2fa(0.0f),
        const embree::Vec3fa& V = embree::Vec3fa(0.0f),
        const uint& geomID = RTC_INVALID_GEOMETRY_ID,
        const uint& primID = RTC_INVALID_GEOMETRY_ID,
        const uint& instID = RTC_INVALID_GEOMETRY_ID)
        : P(P),
        N(N),
        Nw(Nw),
        UV(UV),
        V(V),
        geomID(geomID),
        primID(primID),
        instID(instID)
    {
    }
};

#endif // RENDER_HELPER_H
