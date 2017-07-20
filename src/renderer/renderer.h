#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "random"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        void initRender(int renderWidth, int renderHeight);
        void renderTracer(int renderWidth, int renderHeight, int renderSamples, int renderBounces);
        void initQuadRender();
        void cleanQuadRender();
        void initScene();
        void cleanScene();
        void displayGLBuffer();
        void renderToPPM(int renderWidth, int renderHeight, int renderSamples, int renderBounces);

        inline float clamp(float x);
        inline int hdrToSRGB(float x);

    private:
        int frameCounter = 0;
        int sphereCount;

        GLuint quadVAO;
        GLuint quadVBO;

        glm::vec3* outputBuffer;
        glm::vec3* accumulationBuffer;

        SphereObject* spheresList;

        Shader quadRenderShader;

        std::random_device randSeed;
};


#endif // RENDERER_H
