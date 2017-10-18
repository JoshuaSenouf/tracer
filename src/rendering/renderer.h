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
        void initQuadRender();
        void initScene();
        void traceLoop(int progressiveWidth, int progressiveHeight, int progressiveSamples, int progressiveBounces, int frameCounter, std::vector<Vector3>& renderBuffer);
        void renderToTexture(int textureWidth, int textureHeight, const std::vector<Vector3>& renderBuffer);
        void cleanQuadRender();
        void cleanScene();
        void displayGLBuffer();

    private:
        int sphereCount;

        GLuint quadVAO;
        GLuint quadVBO;
        GLuint renderTextureID;

        Shader quadRenderShader;

        std::vector<Sphere> spheresList;
};


#endif // RENDERER_H
