#include "camera.h"


Camera::Camera()
{

}


void Camera::initCameraData(const cameraData sceneCamera)
{
    cameraPosition = sceneCamera.position;
    cameraYaw = sceneCamera.yaw;
    cameraPitch = sceneCamera.pitch;
    cameraFOV.x = sceneCamera.fov;
    cameraApertureRadius = sceneCamera.apertureRadius;
    cameraFocalDistance = sceneCamera.focalDistance;
    cameraUp = Vector3(0.0f, 1.0f, 0.0f).normalize();
    cameraSpeed = 10.0f;
    cameraSensitivity = 0.10f;

    setCameraFOV(cameraFOV.x);
    updateCameraVectors();
}


void Camera::setCameraResolution(Vector2 tempResolution)
{
    cameraResolution = tempResolution;
}


void Camera::setCameraPosition(Vector3 tempPosition)
{
    cameraPosition = tempPosition;
}


void Camera::setCameraFront(Vector3 tempForward)
{
    cameraFront = tempForward;
}


void Camera::setCameraUp(Vector3 tempUp)
{
    cameraUp = tempUp;
}


void Camera::setCameraRight(Vector3 tempRight)
{
    cameraRight = tempRight;
}


void Camera::setCameraFOV(float tempFOV)
{
    cameraFOV.x = tempFOV;
    cameraFOV.y = (atan(tan(tempFOV * M_PI * M_1_180 * 0.5f) * ((float)cameraResolution.y / (float)cameraResolution.x)) * 2.0f) * 180.0f * M_1_PI;
}


void Camera::Camera::setCameraYaw(float tempYaw)
{
    cameraYaw = fmax(tempYaw, 0.0f);
}


void Camera::Camera::setCameraPitch(float tempPitch)
{
    cameraPitch = fmax(tempPitch, 0.0f);
}


void Camera::Camera::setCameraSpeed(float tempSpeed)
{
    cameraSpeed = fmax(tempSpeed, 0.0f);
}


void Camera::Camera::setCameraSensitivity(float tempSensitivity)
{
    cameraSensitivity = fmax(tempSensitivity, 0.0f);
}


void Camera::Camera::setCameraApertureRadius(float tempAperture)
{
    cameraApertureRadius = fmax(tempAperture, 0.0f);
}


void Camera::setCameraFocalDistance(float tempFocal)
{
    cameraFocalDistance = fmax(tempFocal, 0.01f);
}


Vector2 Camera::getCameraResolution()
{
    return cameraResolution;
}


Vector3 Camera::getCameraPosition()
{
    return cameraPosition;
}


Vector3 Camera::getCameraFront()
{
    return cameraFront;
}


Vector3 Camera::getCameraUp()
{
    return cameraUp;
}


Vector3 Camera::getCameraRight()
{
    return cameraRight;
}


Vector2 Camera::getCameraFOV()
{
    return cameraFOV;
}


float Camera::getCameraYaw()
{
    return cameraYaw;
}


float Camera::getCameraPitch()
{
    return cameraPitch;
}


float Camera::getCameraSpeed()
{
    return cameraSpeed;
}


float Camera::getCameraSensitivity()
{
    return cameraSensitivity;
}


float Camera::getCameraApertureRadius()
{
    return cameraApertureRadius;
}


float Camera::getCameraFocalDistance()
{
    return cameraFocalDistance;
}


void Camera::keyboardCall(cameraMovement direction, GLfloat deltaTime)
{
    GLfloat cameraVelocity = cameraSpeed * deltaTime;

    if (direction == FORWARD)
        cameraPosition += cameraFront * cameraVelocity;
    if (direction == BACKWARD)
        cameraPosition -= cameraFront * cameraVelocity;
    if (direction == LEFT)
        cameraPosition -= cameraRight * cameraVelocity;
    if (direction == RIGHT)
        cameraPosition += cameraRight * cameraVelocity;
}


void Camera::mouseCall(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= cameraSensitivity;
    yoffset *= cameraSensitivity;
    cameraYaw += xoffset;
    cameraPitch += yoffset;

    if (constrainPitch)
    {
        if (cameraPitch > 89.0f)
            cameraPitch = 89.0f;
        if (cameraPitch < -89.0f)
            cameraPitch = -89.0f;
    }

    this->updateCameraVectors();
}


void Camera::updateCameraVectors()
{
    Vector3 tempFront;

    tempFront.x = cos(degreesToRadians(cameraYaw)) * cos(degreesToRadians(cameraPitch));
    tempFront.y = sin(degreesToRadians(cameraPitch));
    tempFront.z = sin(degreesToRadians(cameraYaw)) * cos(degreesToRadians(cameraPitch));
    tempFront *= -1.0f;

    cameraFront = tempFront.normalize();
    cameraRight = cameraFront.cross(cameraUp).normalize();
}


Ray Camera::getCameraRay(int posX, int posY, Randomizer& randEngine)
{
    Vector3 horizontalAxis = cameraFront.cross(cameraUp).normalize();
    Vector3 verticalAxis = horizontalAxis.cross(cameraFront).normalize();

    Vector3 middle = cameraPosition + cameraFront;
    Vector3 horizontal = horizontalAxis * std::tan(cameraFOV.x * 0.5f * (M_PI / 180));
    Vector3 vertical = verticalAxis * std::tan(cameraFOV.y * -0.5f * (M_PI / 180));

    float rayJitterX = ((randEngine.getRandomFloat() - 0.5f) + posX) / (cameraResolution.x - 1.0f);
    float rayJitterY = ((randEngine.getRandomFloat() - 0.5f) + posY) / (cameraResolution.y - 1.0f);

    Vector3 cameraPointOnPlane = cameraPosition
                                + ((middle
                                + (horizontal * ((2.0f * rayJitterX) - 1.0f))
                                + (vertical * ((2.0f * rayJitterY) - 1.0f))
                                - cameraPosition)
                                * cameraFocalDistance);

    Vector3 cameraAperturePoint = cameraPosition;

    if (cameraApertureRadius > 0.0f)
    {
        float randomizedAngle = 2.0f * M_PI * randEngine.getRandomFloat();
        float randomizedRadius = cameraApertureRadius * std::sqrt(randEngine.getRandomFloat());
        float apertureX = std::cos(randomizedAngle) * randomizedRadius;
        float apertureY = std::sin(randomizedAngle) * randomizedRadius;

        cameraAperturePoint = cameraPosition + (horizontalAxis * apertureX) + (verticalAxis * apertureY);
    }

    Vector3 rayOrigin = cameraAperturePoint;
    Vector3 rayDirection = (cameraPointOnPlane - cameraAperturePoint).normalize();

    return Ray(rayOrigin, rayDirection);
}
