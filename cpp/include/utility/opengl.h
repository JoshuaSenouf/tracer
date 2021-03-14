#ifndef OPENGL_UTILITY_H
#define OPENGL_UTILITY_H

#include "glad/glad.h"


static const GLfloat screen_quad_vertices[] =
{
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

#endif // OPENGL_UTILITY_H