#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include <glad/glad.h>
#include "stb_image.h"

#include "scene.h"
#include "shader.h"
#include "vector.h"
#include "randomizer.h"
#include "math_helper.h"


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
        void renderToTexture(int progressiveWidth, int progressiveHeight);
        void cleanFrontBuffer(int progressiveWidth, int progressiveHeight);
        void cleanPPMBuffer();
        void initQuadRender();
        void cleanQuadRender();
        void initScene();
        void cleanScene();
        void displayGLBuffer();
        void exportToPPM(int ppmWidth, int ppmHeight);
        void renderToPPM(int ppmWidth, int ppmHeight, int ppmSamples, int ppmBounces);
        void saveToBackBuffer(int progressiveWidth, int progressiveHeight);
        void swapBuffer(int progressiveWidth, int progressiveHeight);

    private:
        int sphereCount;

        GLuint quadVAO;
        GLuint quadVBO;
        GLuint renderTextureID;

        Shader quadRenderShader;

        std::vector<SphereObject> spheresList;
        std::vector<Vector3> frontBuffer;
        std::vector<Vector3> backBuffer;
        std::vector<Vector3> ppmBuffer;
};


#endif // RENDERER_H
