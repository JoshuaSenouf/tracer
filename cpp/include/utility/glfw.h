#ifndef GLFW_UTILITY_H
#define GLFW_UTILITY_H

#include <stdio.h>


static void GLFWErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

#endif // GLFW_UTILITY_H