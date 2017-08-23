#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "math_helper.h"


enum cameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


struct CameraInfo
{
    glm::vec2 cameraResolution;
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec2 cameraFOV;

    float cameraYaw;
    float cameraPitch;
    float cameraSpeed;
    float cameraSensitivity;
    float cameraApertureRadius;
    float cameraFocalDistance;
};


class Camera
{
    public:
        Camera();

        void setCamera(glm::vec2 tempResolution);
        void initCameraInfo();

        void setCameraResolution(glm::vec2 tempResolution);
        void setCameraPosition(glm::vec3 tempPosition);
        void setCameraFront(glm::vec3 tempForward);
        void setCameraUp(glm::vec3 tempUp);
        void setCameraRight(glm::vec3 tempRight);
        void setCameraFOV(float tempFOV);
        void setCameraYaw(float tempYaw);
        void setCameraPitch(float tempPitch);
        void setCameraSpeed(float tempSpeed);
        void setCameraSensitivity(float tempSensisivity);
        void setCameraApertureRadius(float tempAperture);
        void setCameraFocalDistance(float tempFocal);

        CameraInfo getCameraInfo();
        glm::vec2 getCameraResolution();
        glm::vec3 getCameraPosition();
        glm::vec3 getCameraFront();
        glm::vec3 getCameraUp();
        glm::vec3 getCameraRight();
        glm::vec2 getCameraFOV();
        float getCameraYaw();
        float getCameraPitch();
        float getCameraSpeed();
        float getCameraSensitivity();
        float getCameraApertureRadius();
        float getCameraFocalDistance();

        void keyboardCall(cameraMovement direction, GLfloat deltaTime);
        void mouseCall(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch);

    private:
        void updateCameraVectors();

        CameraInfo cameraInfo;
};

#endif // CAMERA_H
