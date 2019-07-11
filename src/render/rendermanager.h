#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <memory>
#include <vector>

#include <glad/glad.h>
#include "stb_image.h"

#include "buffer.h"
#include "camera.h"
#include "glshader.h"
#include "integrator.h"
#include "ray.h"
#include "scenemanager.h"
#include "sampler.h"

#include "render_helper.h"
#include "tbb_helper.h"

#include "udpt.h"
#include "diffuse.h"
#include "occlusion.h"
#include "position.h"
#include "normal.h"
#include "debug.h"


struct RenderManager
{
    RenderManager();
    ~RenderManager();

    void Trace(const RenderGlobals& renderGlobals,
        SceneManager& sceneManager,
        Camera& camera,
        Buffer& buffer,
        int iterations);
    void RenderToScreenTexture(int width,
        int height,
        Buffer& buffer);
    void SetupScreenQuad(int width,
        int height);
    void CleanScreenQuad();
    void DrawScreenQuad();

    unsigned int integratorID = UDPT;

    private:
        GLuint screenQuadVAO;
        GLuint screenQuadVBO;
        GLuint screenTextureID;

        GLShader screenQuadShader;
        std::vector<std::shared_ptr<Integrator>> integrators {
            std::make_shared<UDPTIntegrator>(),
            std::make_shared<DiffuseIntegrator>(),
            std::make_shared<OcclusionIntegrator>(),
            std::make_shared<PositionIntegrator>(),
            std::make_shared<NormalIntegrator>(),
            std::make_shared<DebugIntegrator>()
        };
};

#endif // RENDERMANAGER_H
