#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include <glad/glad.h>
#include "stb_image.h"

#include "shaderGL.h"
#include "vector.h"
#include "camera.h"
#include "scenemanager.h"
#include "pathtracer.h"


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

        void initRender(int progressiveWidth,
            int progressiveHeight);
        void initQuadRender();
        void traceLoop(int progressiveWidth,
            int progressiveHeight,
            int progressiveSamples,
            int progressiveDepth,
            int frameCounter,
            std::vector<Vector3>& renderBuffer,
            Camera& renderCamera,
            SceneManager& renderScene);
        void renderToTexture(int textureWidth,
            int textureHeight,
            const std::vector<Vector3>& renderBuffer);
        void cleanQuadRender();
        void displayGLBuffer();

    private:
        GLuint quadVAO;
        GLuint quadVBO;
        GLuint renderTextureID;

        ShaderGL quadRenderShader;
        PathTracer renderIntegrator;
};


#endif // RENDERER_H
