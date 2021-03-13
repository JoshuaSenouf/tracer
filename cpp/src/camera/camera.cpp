#include <spdlog/spdlog.h>

#include "utility/math.h"

#include "camera/camera.h"


Camera::Camera()
{
    spdlog::trace("Camera::Camera()");
}

void Camera::Initialize(
    int width,
    int height)
{
    spdlog::trace("Camera::Initialize()");

    // TODO: Hardcoded information for now.
    resolution = embree::Vec2fa(width, height);
    position = embree::Vec3fa(0, 4, 15);
    yaw = 90;
    pitch = 6;
    fov.x = 45;
    aperture_radius = 0;
    focal_distance = 4;

    up = embree::normalize(embree::Vec3fa(0.0f, 1.0f, 0.0f));
    speed = 10.0f;
    sensitivity = 0.10f;

    SetupFOV();
    Update();

    spdlog::debug(
        "Camera::Initialize() - "
        "Camera initialized successfully.");
}

void Camera::SetupFOV()
{
    spdlog::trace("Camera::SetupFOV()");

    fov.y = (
        (atan(tan(fov.x * M_PI * M_1_180 * 0.5f) * ((float)resolution.y / (float)resolution.x))
        * 2.0f) * 180.0f * M_1_PI);
}

void Camera::Update()
{
    spdlog::trace("Camera::Update()");

    front = embree::Vec3fa(
        cos(DegToRad(yaw)) * cos(DegToRad(pitch)),
        sin(DegToRad(pitch)),
        sin(DegToRad(yaw)) * cos(DegToRad(pitch))) * -1.0f;
    front = embree::normalize(front);
    right = embree::normalize(embree::cross(front, up));
}

void Camera::KeyboardCallback(
    CameraMovements direction,
    float delta_time)
{
    float velocity(speed * delta_time);

    if (direction == kForward)
    {
        position += front * velocity;
    }
    if (direction == kBackward)
    {
        position -= front * velocity;
    }
    if (direction == kLeft)
    {
        position -= right * velocity;
    }
    if (direction == kRight)
    {
        position += right * velocity;
    }
}

void Camera::MouseCallback(
    embree::Vec2fa mouse_offset)
{
    mouse_offset *= sensitivity;

    yaw += mouse_offset.x;
    pitch += mouse_offset.y;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    Update();
}
