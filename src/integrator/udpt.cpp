#include "udpt.h"

#include "ray.h"


UDPTIntegrator::UDPTIntegrator()
{
    _handle = "UDPT";
}

embree::Vec3f UDPTIntegrator::GetPixelColor(Ray& ray,
    Sample& pixelSample,
    SceneManager &sceneManager,
    const RenderGlobals& renderGlobals)
{
    embree::Vec3f colorAccumulation(0.0f);
    embree::Vec3f colorMask(1.0f);

    for (int bounce = 0; bounce < renderGlobals.depth; ++bounce)
    {
        RTCIntersectContext intersectContext;
        rtcInitIntersectContext(&intersectContext);

        rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

        if (ray.instID == RTC_INVALID_GEOMETRY_ID)
        {
            // TODO: Hardcoded sky color value for now.
            return colorAccumulation += colorMask * embree::Vec3f(0.7, 0.8, 0.9);
        }

        auto intersectedGeom(sceneManager._sceneGeom[ray.instID].get());

        pxr::GfMatrix4f transform(intersectedGeom->_transform);
        embree::Vec3fa position(ray.origin + ray.tfar * ray.direction);
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

        // From Embree 3.x
        float errorBias = 32.0f * 1.19209e-07f * std::max(
            std::max(std::abs(shadingPoint.P.x), abs(shadingPoint.P.y)), 
            std::max(std::abs(shadingPoint.P.z), ray.tfar));

        const float rand0 = pixelSample.sampler.Uniform1D();
        const float rand1 = pixelSample.sampler.Uniform1D();
        const float r = std::sqrt(rand0);
        const float theta = 2.0f * M_PI * rand1;
        const float x = r * std::cos(theta);
        const float y = r * std::sin(theta);

        embree::Vec3fa u(embree::normalize(embree::cross(shadingPoint.Nw,
            pixelSample.sampler.SphereUniform(pixelSample.sampler.Uniform1D(),
                pixelSample.sampler.Uniform1D()))));
        embree::Vec3fa v(embree::cross(shadingPoint.Nw, u));

        embree::Vec3fa sampleDirection(shadingPoint.Nw * std::sqrt(1 - rand1));
        sampleDirection += (u * x);
        sampleDirection += (v * y);

        float positionSign(embree::dot(sampleDirection, shadingPoint.Nw) < 0.0f ? -1.0f : 1.0f);
        ray.origin = position + (positionSign * errorBias * shadingPoint.Nw);
        ray.direction = sampleDirection;

        // Initializing the new ray.
        ray = Ray(ray.origin, ray.direction, errorBias);

        colorMask = colorMask * embree::Vec3f(intersectedGeom->_displayColor * (1.0f / M_PI));
    }

    return colorAccumulation;
}
