#include "math_helper.h"

#include "camera.h"


Camera::Camera()
{

}


void Camera::initCameraData(const cameraData sceneCamera)
{
    this->position = sceneCamera.position;
    this->yaw = sceneCamera.yaw;
    this->pitch = sceneCamera.pitch;
    this->FOV.x = sceneCamera.FOV;
    this->apertureRadius = sceneCamera.apertureRadius;
    this->focalDistance = sceneCamera.focalDistance;
    this->up = Vector3(0.0f, 1.0f, 0.0f).normalize();
    this->speed = 10.0f;
    this->sensitivity = 0.10f;

    setFOV(FOV.x);
    updateCameraVectors();
}


void Camera::updateCameraVectors()
{
    Vector3 tempFront;

    tempFront.x = cos(degreesToRadians(this->yaw)) * cos(degreesToRadians(this->pitch));
    tempFront.y = sin(degreesToRadians(this->pitch));
    tempFront.z = sin(degreesToRadians(this->yaw)) * cos(degreesToRadians(this->pitch));
    tempFront *= -1.0f;

    this->front = tempFront.normalize();
    this->right = this->front.cross(this->up).normalize();
}


Ray Camera::getCameraRay(int posX,
    int posY,
    Randomizer& randEngine)
{
    Vector3 horizontalAxis = this->front.cross(this->up).normalize();
    Vector3 verticalAxis = horizontalAxis.cross(this->front).normalize();

    Vector3 middle = this->position + this->front;
    Vector3 horizontal = horizontalAxis * std::tan(this->FOV.x * 0.5f * (M_PI / 180));
    Vector3 vertical = verticalAxis * std::tan(this->FOV.y * -0.5f * (M_PI / 180));

    float rayJitterX = ((randEngine.getRandomFloat() - 0.5f) + posX) / (this->resolution.x - 1.0f);
    float rayJitterY = ((randEngine.getRandomFloat() - 0.5f) + posY) / (this->resolution.y - 1.0f);

    Vector3 pointOnPlane = this->position
                                + ((middle
                                + (horizontal * ((2.0f * rayJitterX) - 1.0f))
                                + (vertical * ((2.0f * rayJitterY) - 1.0f))
                                - this->position)
                                * this->focalDistance);

    Vector3 aperturePoint = this->position;

    if (this->apertureRadius > 0.0f)
    {
        float randomizedAngle = 2.0f * M_PI * randEngine.getRandomFloat();
        float randomizedRadius = this->apertureRadius * std::sqrt(randEngine.getRandomFloat());
        float apertureX = std::cos(randomizedAngle) * randomizedRadius;
        float apertureY = std::sin(randomizedAngle) * randomizedRadius;

        aperturePoint = this->position + (horizontalAxis * apertureX) + (verticalAxis * apertureY);
    }

    Vector3 rayOrigin = aperturePoint;
    Vector3 rayDirection = (pointOnPlane - aperturePoint).normalize();

    return Ray(rayOrigin, rayDirection);
}


Vector2& Camera::getResolution()
{
    return this->resolution;
}


Vector3& Camera::getPosition()
{
    return this->position;
}


Vector3& Camera::getFront()
{
    return this->front;
}


Vector3& Camera::getUp()
{
    return this->up;
}


Vector3& Camera::getRight()
{
    return this->right;
}


Vector2& Camera::getFOV()
{
    return this->FOV;
}


float& Camera::getYaw()
{
    return this->yaw;
}


float& Camera::getPitch()
{
    return this->pitch;
}


float& Camera::getSpeed()
{
    return this->speed;
}


float& Camera::getSensitivity()
{
    return this->sensitivity;
}


float& Camera::getApertureRadius()
{
    return this->apertureRadius;
}


float& Camera::getFocalDistance()
{
    return this->focalDistance;
}


void Camera::setResolution(Vector2 tempResolution)
{
    this->resolution = tempResolution;
}


void Camera::setPosition(Vector3 tempPosition)
{
    this->position = tempPosition;
}


void Camera::setFront(Vector3 tempForward)
{
    this->front = tempForward;
}


void Camera::setUp(Vector3 tempUp)
{
    this->up = tempUp;
}


void Camera::setRight(Vector3 tempRight)
{
    this->right = tempRight;
}


void Camera::setFOV(float tempFOV)
{
    this->FOV.x = tempFOV;
    this->FOV.y = (atan(tan(tempFOV * M_PI * M_1_180 * 0.5f)
        * ((float)this->resolution.y / (float)this->resolution.x)) * 2.0f)
        * 180.0f * M_1_PI;
}


void Camera::setYaw(float tempYaw)
{
    this->yaw = fmax(tempYaw, 0.0f);
}


void Camera::setPitch(float tempPitch)
{
    this->pitch = fmax(tempPitch, 0.0f);
}


void Camera::setSpeed(float tempSpeed)
{
    this->speed = fmax(tempSpeed, 0.0f);
}


void Camera::setSensitivity(float tempSensitivity)
{
    this->sensitivity = fmax(tempSensitivity, 0.0f);
}


void Camera::setApertureRadius(float tempAperture)
{
    this->apertureRadius = fmax(tempAperture, 0.0f);
}


void Camera::setFocalDistance(float tempFocal)
{
    this->focalDistance = fmax(tempFocal, 0.01f);
}


void Camera::keyboardCall(cameraMovement direction,
    GLfloat deltaTime)
{
    GLfloat velocity = this->speed * deltaTime;

    if (direction == FORWARD)
        this->position += this->front * velocity;
    if (direction == BACKWARD)
        this->position -= this->front * velocity;
    if (direction == LEFT)
        this->position -= this->right * velocity;
    if (direction == RIGHT)
        this->position += this->right * velocity;
}


void Camera::mouseCall(GLfloat xoffset,
    GLfloat yoffset,
    GLboolean constrainPitch)
{
    xoffset *= this->sensitivity;
    yoffset *= this->sensitivity;
    this->yaw += xoffset;
    this->pitch += yoffset;

    if (constrainPitch)
    {
        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;
    }

    updateCameraVectors();
}
