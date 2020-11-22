#ifndef CAMERA_H
#define CAMERA_H

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>

#include "utility/camera_helper.h"


struct Camera
{
    Camera();

    void Initialize(
        int width,
        int height);
    void Update();
    void SetupFOV();
    void KeyboardCallback(
        CameraMovements direction,
        float delta_time);
    void MouseCallback(
        embree::Vec2fa mouse_offset);

    bool jitter_rays = true;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float aperture_radius;
    float focal_distance;
    embree::Vec2fa resolution;
    embree::Vec2fa fov;
    embree::Vec3fa position;
    embree::Vec3fa front;
    embree::Vec3fa up;
    embree::Vec3fa right;
};

#endif // CAMERA_H
