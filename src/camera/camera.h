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
        void keyboardCall(cameraMovement direction,
            GLfloat deltaTime);
        void mouseCall(GLfloat xoffset,
            GLfloat yoffset,
            GLboolean constrainPitch);
        void updateCameraVectors();
        Ray getCameraRay(int posX,
            int posY,
            Randomizer& randEngine);

        Vector2& getResolution();
        Vector3& getPosition();
        Vector3& getFront();
        Vector3& getUp();
        Vector3& getRight();
        Vector2& getFOV();
        float& getYaw();
        float& getPitch();
        float& getSpeed();
        float& getSensitivity();
        float& getApertureRadius();
        float& getFocalDistance();

        void setResolution(Vector2 tempResolution);
        void setPosition(Vector3 tempPosition);
        void setFront(Vector3 tempForward);
        void setUp(Vector3 tempUp);
        void setRight(Vector3 tempRight);
        void setFOV(float tempFOV);
        void setYaw(float tempYaw);
        void setPitch(float tempPitch);
        void setSpeed(float tempSpeed);
        void setSensitivity(float tempSensisivity);
        void setApertureRadius(float tempAperture);
        void setFocalDistance(float tempFocal);

    private:
        Vector2 resolution;
        Vector3 position;
        Vector3 front;
        Vector3 up;
        Vector3 right;
        Vector2 FOV;

        float yaw;
        float pitch;
        float speed;
        float sensitivity;
        float apertureRadius;
        float focalDistance;
};

#endif // CAMERA_H
