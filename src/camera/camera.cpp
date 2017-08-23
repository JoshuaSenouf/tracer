#include "camera.h"


Camera::Camera()
{

}


void Camera::setCamera(glm::vec2 tempResolution)
{
    initCameraInfo();
    setCameraResolution(tempResolution);
}


void Camera::initCameraInfo()
{
    cameraInfo.cameraPosition = glm::vec3(0.0f, 4.0f, 15.0f); // (0.0f, 4.0f, 15.0f) Test, (0.0f, 2.9f, 17.0f) Cornell
    cameraInfo.cameraUp = normalize(glm::vec3(0.0f, 1.0f, 0.0f));
    cameraInfo.cameraYaw = 90.0f;
    cameraInfo.cameraPitch = 6.0f; // 6.0f Test, 2.0f Cornell
    cameraInfo.cameraFOV.x = 45.0f;
    cameraInfo.cameraApertureRadius = 0.0f;
    cameraInfo.cameraFocalDistance = 4.0f;
    cameraInfo.cameraSpeed = 10.0f;
    cameraInfo.cameraSensitivity = 0.10f;

    updateCameraVectors();
}


void Camera::setCameraResolution(glm::vec2 tempResolution)
{
    cameraInfo.cameraResolution = tempResolution;
    setCameraFOV(cameraInfo.cameraFOV.x);
}


void Camera::setCameraPosition(glm::vec3 tempPosition)
{
    cameraInfo.cameraPosition = tempPosition;
}


void Camera::setCameraFront(glm::vec3 tempForward)
{
    cameraInfo.cameraFront = tempForward;
}


void Camera::setCameraUp(glm::vec3 tempUp)
{
    cameraInfo.cameraUp = tempUp;
}


void Camera::setCameraRight(glm::vec3 tempRight)
{
    cameraInfo.cameraRight = tempRight;
}


void Camera::setCameraFOV(float tempFOV)
{
    cameraInfo.cameraFOV.x = tempFOV;
    cameraInfo.cameraFOV.y = (atan(tan(tempFOV * M_PI * M_1_180 * 0.5f) * ((float)cameraInfo.cameraResolution.y / (float)cameraInfo.cameraResolution.x)) * 2.0f) * 180.0f * M_1_PI;
}


void Camera::Camera::setCameraYaw(float tempYaw)
{
    cameraInfo.cameraYaw = fmax(tempYaw, 0.0f);
}


void Camera::Camera::setCameraPitch(float tempPitch)
{
    cameraInfo.cameraPitch = fmax(tempPitch, 0.0f);
}


void Camera::Camera::setCameraSpeed(float tempSpeed)
{
    cameraInfo.cameraSpeed = fmax(tempSpeed, 0.0f);
}


void Camera::Camera::setCameraSensitivity(float tempSensitivity)
{
    cameraInfo.cameraSensitivity = fmax(tempSensitivity, 0.0f);
}


void Camera::Camera::setCameraApertureRadius(float tempAperture)
{
    cameraInfo.cameraApertureRadius = fmax(tempAperture, 0.0f);
}


void Camera::setCameraFocalDistance(float tempFocal)
{
    cameraInfo.cameraFocalDistance = fmax(tempFocal, 0.01f);
}


CameraInfo Camera::getCameraInfo()
{
    return cameraInfo;
}


glm::vec2 Camera::getCameraResolution()
{
    return cameraInfo.cameraResolution;
}


glm::vec3 Camera::getCameraPosition()
{
    return cameraInfo.cameraPosition;
}


glm::vec3 Camera::getCameraFront()
{
    return cameraInfo.cameraFront;
}


glm::vec3 Camera::getCameraUp()
{
    return cameraInfo.cameraUp;
}


glm::vec3 Camera::getCameraRight()
{
    return cameraInfo.cameraRight;
}


glm::vec2 Camera::getCameraFOV()
{
    return cameraInfo.cameraFOV;
}


float Camera::getCameraYaw()
{
    return cameraInfo.cameraYaw;
}


float Camera::getCameraPitch()
{
    return cameraInfo.cameraPitch;
}


float Camera::getCameraSpeed()
{
    return cameraInfo.cameraSpeed;
}


float Camera::getCameraSensitivity()
{
    return cameraInfo.cameraSensitivity;
}


float Camera::getCameraApertureRadius()
{
    return cameraInfo.cameraApertureRadius;
}


float Camera::getCameraFocalDistance()
{
    return cameraInfo.cameraFocalDistance;
}


void Camera::keyboardCall(cameraMovement direction, GLfloat deltaTime)
{
    GLfloat cameraVelocity = cameraInfo.cameraSpeed * deltaTime;

    if (direction == FORWARD)
        cameraInfo.cameraPosition += cameraInfo.cameraFront * cameraVelocity;
    if (direction == BACKWARD)
        cameraInfo.cameraPosition -= cameraInfo.cameraFront * cameraVelocity;
    if (direction == LEFT)
        cameraInfo.cameraPosition -= cameraInfo.cameraRight * cameraVelocity;
    if (direction == RIGHT)
        cameraInfo.cameraPosition += cameraInfo.cameraRight * cameraVelocity;
}


void Camera::mouseCall(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= cameraInfo.cameraSensitivity;
    yoffset *= cameraInfo.cameraSensitivity;
    cameraInfo.cameraYaw += xoffset;
    cameraInfo.cameraPitch += yoffset;

    if (constrainPitch)
    {
        if (cameraInfo.cameraPitch > 89.0f)
            cameraInfo.cameraPitch = 89.0f;
        if (cameraInfo.cameraPitch < -89.0f)
            cameraInfo.cameraPitch = -89.0f;
    }

    this->updateCameraVectors();
}


void Camera::updateCameraVectors()
{
    glm::vec3 tempFront;
    tempFront.x = cos(glm::radians(cameraInfo.cameraYaw)) * cos(glm::radians(cameraInfo.cameraPitch));
    tempFront.y = sin(glm::radians(cameraInfo.cameraPitch));
    tempFront.z = sin(glm::radians(cameraInfo.cameraYaw)) * cos(glm::radians(cameraInfo.cameraPitch));
    tempFront *= -1.0f;

    cameraInfo.cameraFront = normalize(tempFront);
    cameraInfo.cameraRight = normalize(cross(cameraInfo.cameraFront, cameraInfo.cameraUp));
}
