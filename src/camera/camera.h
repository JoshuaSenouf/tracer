#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

#include "vector.h"
#include "ray.h"
#include "randomizer.h"
#include "camera_helper.h"
#include "render_helper.h"
#include "embree_helper.h"


struct Camera
{
    Camera();

    void init();
    void keyboardCallback(CAMERA_MOVEMENTS direction,
        GLfloat deltaTime);
    void mouseCallback(GLfloat offsetX,
        GLfloat offsetY,
        GLboolean constrainPitch);
    void updateVectors();
    Ray getCameraRay(int posX,
        int posY,
        Randomizer& randEngine);

    void setupFOV();

    Vector2 _resolution;
    Vector3 _position;
    Vector3 _front;
    Vector3 _up;
    Vector3 _right;
    Vector2 _fov;

    float _yaw;
    float _pitch;
    float _speed;
    float _sensitivity;
    float _apertureRadius;
    float _focalDistance;
};

#endif // CAMERA_H
