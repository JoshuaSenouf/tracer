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
#include "tinyexr.h"


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
        void initQuadRender();
        void initScene();
        std::vector<Vector3> traceLoop(int progressiveWidth, int progressiveHeight, int progressiveSamples, int progressiveBounces, int frameCounter, std::vector<Vector3> renderBuffer = {});
        void renderToTexture(int textureWidth, int textureHeight, std::vector<Vector3> renderBuffer);
        void cleanQuadRender();
        void cleanScene();
        void cleanBuffer(int bufferWidth, int bufferHeight, std::vector<Vector3> &buffer);
        void cleanFrontBuffer(int progressiveWidth, int progressiveHeight);
        void displayGLBuffer();
        void exportToPPM(int ppmWidth, int ppmHeight, std::vector<Vector3> exportBuffer = {});
        void exportToEXR(int exrWidth, int exrHeight, std::vector<Vector3> exportBuffer = {});
        void renderToPPM(int ppmWidth, int ppmHeight, int ppmSamples, int ppmBounces);
        void renderToEXR(int exrWidth, int exrHeight, int exrSamples, int exrBounces);
        void saveToBackBuffer(int progressiveWidth, int progressiveHeight);
        void swapBuffer(int progressiveWidth, int progressiveHeight);

        std::vector<Vector3> getFrontBuffer();
        void setFrontBuffer(std::vector<Vector3> buffer);

    private:
        bool frontUsed;

        int sphereCount;

        GLuint quadVAO;
        GLuint quadVBO;
        GLuint renderTextureID;

        Shader quadRenderShader;

        std::vector<SphereObject> spheresList;
        std::vector<Vector3> frontBuffer;
        std::vector<Vector3> backBuffer;
        std::vector<Vector3> ppmBuffer;
        std::vector<Vector3> exrBuffer;
};


#endif // RENDERER_H
