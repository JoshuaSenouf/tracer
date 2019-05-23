#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <memory>

#include <glad/glad.h>
#include "stb_image.h"

#include "camera.h"
#include "buffer.h"
#include "scenemanager.h"
#include "integrator.h"
#include "glshader.h"
#include "render_helper.h"


static const GLfloat screenQuadVertices[] =
{
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};


class RenderManager
{
    public:
        RenderManager();
        ~RenderManager();

        void setupScreenQuad(int width,
            int height);
        void trace(int width,
            int height,
            int samples,
            int depth,
            int frame,
            Buffer& buffer,
            Camera& camera,
            SceneManager& sceneManager);
        void renderToScreenTexture(int width,
            int height,
            Buffer& buffer);
        void cleanScreenQuad();
        void drawScreenQuad();
        bool setupIntegrator(int id);

    private:
        GLuint screenQuadVAO;
        GLuint screenQuadVBO;
        GLuint screenTextureID;

        GLShader screenQuadShader;

        unsigned int integratorID = DIFFUSE;

        std::vector<std::shared_ptr<Integrator>> integrators;
};

#endif // RENDERMANAGER_H
