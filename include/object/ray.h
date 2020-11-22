#ifndef RAY_H
#define RAY_H

#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "camera/camera.h"
#include "sampling/sampler.h"
#include "utility/render_helper.h"


struct Ray
{
    embree::Vec3fa origin;
    embree::Vec3fa direction;

    float t_far;
    unsigned int mask;
    unsigned int id;
    unsigned int flags;

    embree::Vec3f Ng;
    float u;
    float v;
    unsigned int prim_id;
    unsigned int geom_id;
    unsigned int inst_id;

    __forceinline Ray(
        const embree::Vec3fa &origin,
        const embree::Vec3fa &direction,
        float t_near = 0.0f,
        float t_far = std::numeric_limits<float>::infinity(),
        float time = 0.0f,
        int mask = -1,
        unsigned int geom_id = RTC_INVALID_GEOMETRY_ID,
        unsigned int prim_id = RTC_INVALID_GEOMETRY_ID,
        unsigned int inst_id = RTC_INVALID_GEOMETRY_ID)
        : origin(origin, t_near),
        direction(direction, time),
        t_far(t_far),
        mask(mask),
        prim_id(prim_id),
        geom_id(geom_id),
        inst_id(inst_id)
    {
    }

    __forceinline Ray(
        const Camera &camera,
        const PixelSample &pixel_sample,
        float t_near = 0.0f,
        float t_far = std::numeric_limits<float>::infinity(),
        float time = 0.0f,
        int mask = -1,
        unsigned int geom_id = RTC_INVALID_GEOMETRY_ID,
        unsigned int prim_id = RTC_INVALID_GEOMETRY_ID,
        unsigned int inst_id = RTC_INVALID_GEOMETRY_ID)
        : t_far(t_far),
        mask(mask),
        prim_id(prim_id),
        geom_id(geom_id),
        inst_id(inst_id)
    {
        embree::Vec3fa axis_x(embree::normalize(embree::cross(camera.front, camera.up)));
        embree::Vec3fa axis_y(embree::normalize(embree::cross(axis_x, camera.front)));
        embree::Vec3fa forward(camera.position + camera.front);
        embree::Vec3fa vector_x(axis_x * std::tan(camera.fov.x * 0.5f * (M_PI / 180)));
        embree::Vec3fa vector_y(axis_y * std::tan(camera.fov.y * -0.5f * (M_PI / 180)));

        float point_x((((camera.jitter_rays ? pixel_sample.sampler.Uniform1D() : 0.0f) - 0.5f) + pixel_sample.pixel_x)
            / (camera.resolution.x - 1.0f));
        float point_y((((camera.jitter_rays ? pixel_sample.sampler.Uniform1D() : 0.0f) - 0.5f) + pixel_sample.pixel_y)
            / (camera.resolution.y - 1.0f));

        embree::Vec3fa point_on_plane(camera.position
            + ((forward
            + (vector_x * ((2.0f * point_x) - 1.0f))
            + (vector_y * ((2.0f * point_y) - 1.0f))
            - camera.position)
            * camera.focal_distance));
        embree::Vec3fa aperture_point(camera.position);

        if (camera.aperture_radius > 0.0f)
        {
            float random_angle(2.0f * M_PI * pixel_sample.sampler.Uniform1D());
            float random_radius(camera.aperture_radius * embree::sqrt(pixel_sample.sampler.Uniform1D()));
            float aperture_x(embree::cos(random_angle) * random_radius);
            float aperture_y(embree::sin(random_angle) * random_radius);

            aperture_point = camera.position + (axis_x * aperture_x) + (axis_y * aperture_y);
        }

        origin = embree::Vec3fa(aperture_point, t_near);
        direction = embree::Vec3fa(embree::normalize(point_on_plane - aperture_point), time);
    }
};

__forceinline RTCRay *RTCRay_(
    Ray &ray)
{
    return (RTCRay *) &ray;
}

__forceinline RTCRayHit *RTCRayHit_(
    Ray &ray)
{
    return (RTCRayHit *) &ray;
}

#endif // RAY_H
