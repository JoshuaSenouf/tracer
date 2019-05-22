#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

#include "camera_helper.h"
#include "render_helper.h"
#include "embree_helper.h"
#include "math_helper.h"


struct Camera
{
    Camera();

    void init();
    void updateVectors();
    void setupFOV();
    void keyboardCallback(CAMERA_MOVEMENTS direction,
        GLfloat deltaTime);
    void mouseCallback(GLfloat offsetX,
        GLfloat offsetY,
        GLboolean constrainPitch);

    embree::Vec2fa _resolution;
    embree::Vec2fa _fov;
    embree::Vec3fa _position;
    embree::Vec3fa _front;
    embree::Vec3fa _up;
    embree::Vec3fa _right;

    float _yaw;
    float _pitch;
    float _speed;
    float _sensitivity;
    float _apertureRadius;
    float _focalDistance;

    bool _doJitter = true;
};

#endif // CAMERA_H
