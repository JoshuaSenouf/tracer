#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scene.h"
#include "shader.h"
#include "vector.h"


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
        ~Renderer();

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

        SphereObject* spheresList;

        Shader quadRenderShader;

        std::random_device randSeed;

        Vector3* accumulationBuffer;
        Vector3* ppmBuffer;
};


#endif // RENDERER_H
