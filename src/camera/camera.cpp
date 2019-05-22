#include "camera.h"


Camera::Camera()
{

}

void Camera::init()
{
    // TODO: Hardcoded information for now.
    _position = embree::Vec3fa(0, 4, 15);
    _yaw = 90;
    _pitch = 6;
    _fov.x = 45;
    _apertureRadius = 0;
    _focalDistance = 4;

    _up = embree::normalize(embree::Vec3fa(0.0f, 1.0f, 0.0f));
    _speed = 10.0f;
    _sensitivity = 0.10f;

    setupFOV();

    updateVectors();
}

void Camera::setupFOV()
{
    _fov.y = (atan(tan(_fov.x * M_PI * M_1_180 * 0.5f)
        * ((float)_resolution.y / (float)_resolution.x)) * 2.0f)
        * 180.0f * M_1_PI;
}

void Camera::updateVectors()
{
    embree::Vec3fa front(cos(degToRad(_yaw)) * cos(degToRad(_pitch)),
        sin(degToRad(_pitch)),
        sin(degToRad(_yaw)) * cos(degToRad(_pitch))
    );

    front *= -1.0f;

    _front = embree::normalize(front);
    _right = embree::normalize(embree::cross(_front, _up));
}

void Camera::keyboardCallback(CAMERA_MOVEMENTS direction,
    GLfloat deltaTime)
{
    GLfloat velocity(_speed * deltaTime);

    if (direction == FORWARD)
    {
        _position += _front * velocity;
    }
    if (direction == BACKWARD)
    {
        _position -= _front * velocity;
    }
    if (direction == LEFT)
    {
        _position -= _right * velocity;
    }
    if (direction == RIGHT)
    {
        _position += _right * velocity;
    }
}

void Camera::mouseCallback(GLfloat offsetX,
    GLfloat offsetY,
    GLboolean constrainPitch)
{
    offsetX *= _sensitivity;
    offsetY *= _sensitivity;
    _yaw += offsetX;
    _pitch += offsetY;

    if (constrainPitch)
    {
        if (_pitch > 89.0f)
        {
            _pitch = 89.0f;
        }
        if (_pitch < -89.0f)
        {
            _pitch = -89.0f;
        }
    }

    updateVectors();
}
