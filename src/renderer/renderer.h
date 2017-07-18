#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gui.h"
#include "camera.h"
#include "scene.h"
#include "shader.h"


static GLfloat quadVertices[] =
{
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};


class Renderer
{
    public:
        Renderer();
        int runRenderer();
        void initQuadRender();
        void cleanQuadRender();
        void initScene();
        void cleanScene();
        void resetRender();
        void displayGLBuffer();

        void keyboardCallback(ImGuiIO* guiIO);
        void mouseCallback(ImGuiIO* guiIO, float mousePosX, float mousePosY);

    private:
        bool firstMouse = true;
        bool guiIsOpen = true;
        bool renderReset = false;

        int frameCounter = 0;
        int sphereCount;

        GLuint renderWidth = 800;
        GLuint renderHeight = 600;
        GLuint renderSamples = 4;
        GLuint renderBounces = 4;
        GLuint quadVAO;
        GLuint quadVBO;

        GLfloat deltaTime = 0.0f;
        GLfloat lastFrame = 0.0f;
        GLfloat lastPosX = renderWidth / 2;
        GLfloat lastPosY = renderHeight / 2;

        glm::vec3* outputBuffer;
        glm::vec3* accumulationBuffer;

        SphereObject* spheresList;

        GLFWwindow* window;

        GUI lumenGUI;

        Camera renderCamera;
        CameraInfo* renderCameraInfo;

        Shader quadRenderShader;
};


#endif // RENDERER_H
