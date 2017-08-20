#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "scene.h"
#include "shader.h"
#include "vector.h"
#include "randomizer.h"


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

        void initRender(int progressiveWidth, int progressiveHeight);
        void renderTracer(int progressiveWidth, int progressiveHeight, int progressiveSamples, int progressiveBounces, int frameCounter);
        void initQuadRender();
        void cleanQuadRender();
        void initScene();
        void cleanScene();
        void displayGLBuffer();
        void renderToPPM(int ppmWidth, int ppmHeight, int ppmSamples, int ppmBounces);

        inline float clamp(float x);
        inline float convertToSRGB(float x);
        inline float convertToLinear(float x);
        inline int convertToRGB(float x);

    private:
        int sphereCount;

        GLuint quadVAO;
        GLuint quadVBO;
        GLuint renderTextureID;

        Shader quadRenderShader;

        SphereObject* spheresList;

        Vector3* accumulationBuffer;
        Vector3* ppmBuffer;

        Randomizer randEngine;
};


#endif // RENDERER_H
