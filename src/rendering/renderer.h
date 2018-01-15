#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include <glad/glad.h>
#include "stb_image.h"

#include "shader.h"
#include "vector.h"
#include "randomizer.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "scene.h"
#include "math_helper.h"
#include "integrator.h"


const GLfloat quadVertices[] =
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
        void traceLoop(int progressiveWidth,
                       int progressiveHeight,
                       int progressiveSamples,
                       int progressiveDepth,
                       int frameCounter,
                       std::vector<Vector3>& renderBuffer,
                       Camera& renderCamera,
                       Scene& renderScene);
        void renderToTexture(int textureWidth, int textureHeight, const std::vector<Vector3>& renderBuffer);
        void cleanQuadRender();
        void displayGLBuffer();

    private:
        GLuint quadVAO;
        GLuint quadVBO;
        GLuint renderTextureID;

        Shader quadRenderShader;
        PathTracer renderIntegrator;
};


#endif // RENDERER_H
