#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

#include "vector.h"
#include "ray.h"
#include "randomizer.h"
#include "render_helper.h"


enum cameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class Camera
{
    public:
        Camera();

        void initCameraData(const cameraData sceneCameraData);

        void setCameraResolution(Vector2 tempResolution);
        void setCameraPosition(Vector3 tempPosition);
        void setCameraFront(Vector3 tempForward);
        void setCameraUp(Vector3 tempUp);
        void setCameraRight(Vector3 tempRight);
        void setCameraFOV(float tempFOV);
        void setCameraYaw(float tempYaw);
        void setCameraPitch(float tempPitch);
        void setCameraSpeed(float tempSpeed);
        void setCameraSensitivity(float tempSensisivity);
        void setCameraApertureRadius(float tempAperture);
        void setCameraFocalDistance(float tempFocal);

        Vector2 getCameraResolution();
        Vector3 getCameraPosition();
        Vector3 getCameraFront();
        Vector3 getCameraUp();
        Vector3 getCameraRight();
        Vector2 getCameraFOV();
        float getCameraYaw();
        float getCameraPitch();
        float getCameraSpeed();
        float getCameraSensitivity();
        float getCameraApertureRadius();
        float getCameraFocalDistance();

        void keyboardCall(cameraMovement direction, GLfloat deltaTime);
        void mouseCall(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch);

        Ray getCameraRay(int posX, int posY, Randomizer& randEngine);

    private:
        void updateCameraVectors();

        Vector2 cameraResolution;
        Vector3 cameraPosition;
        Vector3 cameraFront;
        Vector3 cameraUp;
        Vector3 cameraRight;
        Vector2 cameraFOV;

        float cameraYaw;
        float cameraPitch;
        float cameraSpeed;
        float cameraSensitivity;
        float cameraApertureRadius;
        float cameraFocalDistance;
};

#endif // CAMERA_H
