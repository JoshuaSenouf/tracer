#include "math_helper.h"

#include "camera.h"


Camera::Camera()
{

}


void Camera::init()
{
    // TODO: Hardcoded information for now.
    _position = Vector3(0, 4, 15);
    _yaw = 90;
    _pitch = 6;
    _fov.x = 45;
    _apertureRadius = 0;
    _focalDistance = 4;

    _up = Vector3(0.0f, 1.0f, 0.0f).normalize();
    _speed = 10.0f;
    _sensitivity = 0.10f;

    setupFOV();

    updateVectors();
}


void Camera::updateVectors()
{
    Vector3 front;

    front.x = cos(degreesToRadians(_yaw)) * cos(degreesToRadians(_pitch));
    front.y = sin(degreesToRadians(_pitch));
    front.z = sin(degreesToRadians(_yaw)) * cos(degreesToRadians(_pitch));
    front *= -1.0f;

    _front = front.normalize();
    _right = _front.cross(_up).normalize();
}


Ray Camera::getCameraRay(int posX,
    int posY,
    Randomizer& randEngine)
{
    Vector3 horizontalAxis = _front.cross(_up).normalize();
    Vector3 verticalAxis = horizontalAxis.cross(_front).normalize();

    Vector3 middle = _position + _front;
    Vector3 horizontal = horizontalAxis * std::tan(_fov.x * 0.5f * (M_PI / 180));
    Vector3 vertical = verticalAxis * std::tan(_fov.y * -0.5f * (M_PI / 180));

    float rayJitterX = ((randEngine.getRandomFloat() - 0.5f) + posX) / (_resolution.x - 1.0f);
    float rayJitterY = ((randEngine.getRandomFloat() - 0.5f) + posY) / (_resolution.y - 1.0f);

    Vector3 pointOnPlane = _position
        + ((middle
        + (horizontal * ((2.0f * rayJitterX) - 1.0f))
        + (vertical * ((2.0f * rayJitterY) - 1.0f))
        - _position)
        * _focalDistance);

    Vector3 aperturePoint = _position;

    if (_apertureRadius > 0.0f)
    {
        float randomizedAngle = 2.0f * M_PI * randEngine.getRandomFloat();
        float randomizedRadius = _apertureRadius * std::sqrt(randEngine.getRandomFloat());
        float apertureX = std::cos(randomizedAngle) * randomizedRadius;
        float apertureY = std::sin(randomizedAngle) * randomizedRadius;

        aperturePoint = _position + (horizontalAxis * apertureX) + (verticalAxis * apertureY);
    }

    Vector3 rayOrigin = aperturePoint;
    Vector3 rayDirection = (pointOnPlane - aperturePoint).normalize();

    return Ray(embree::Vec3fa(rayOrigin.x, rayOrigin.y, rayOrigin.z),
        embree::Vec3fa(rayDirection.x, rayDirection.y, rayDirection.z));
}

void Camera::setupFOV()
{
    _fov.y = (atan(tan(_fov.x * M_PI * M_1_180 * 0.5f)
        * ((float)_resolution.y / (float)_resolution.x)) * 2.0f)
        * 180.0f * M_1_PI;
}

void Camera::keyboardCallback(CAMERA_MOVEMENTS direction,
    GLfloat deltaTime)
{
    GLfloat velocity = _speed * deltaTime;

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
