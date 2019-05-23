#include "rendermanager.h"

#include "ray.h"
#include "randomizer.h"
#include "udpt.h"
#include "diffuse.h"
#include "occlusion.h"
#include "debug.h"
#include "tbb_helper.h"


RenderManager::RenderManager()
{
    std::shared_ptr<UDPTIntegrator> udptIntegrator(std::make_shared<UDPTIntegrator>());
    std::shared_ptr<DiffuseIntegrator> diffuseIntegrator(std::make_shared<DiffuseIntegrator>());
    std::shared_ptr<OcclusionIntegrator> occlusionIntegrator(std::make_shared<OcclusionIntegrator>());
    std::shared_ptr<DebugIntegrator> debugIntegrator(std::make_shared<DebugIntegrator>());

    integrators.push_back(udptIntegrator);
    integrators.push_back(diffuseIntegrator);
    integrators.push_back(occlusionIntegrator);
    integrators.push_back(debugIntegrator);
}

RenderManager::~RenderManager()
{

}

void RenderManager::setupScreenQuad(int width,
    int height)
{
    // Screen quad geometry.
    glGenVertexArrays(1, &screenQuadVAO);
    glGenBuffers(1, &screenQuadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuadVertices), screenQuadVertices, GL_STATIC_DRAW);

    glBindVertexArray(screenQuadVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);

    // Screen quad shader and texture.
    screenQuadShader.setup("res/shaders/screenQuad.vert",
        "res/shaders/screenQuad.frag");

    glGenTextures(1, &screenTextureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, screenTextureID);

    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, width, height);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderManager::trace(int width,
    int height,
    int samples,
    int depth,
    int frame,
    Buffer& buffer,
    Camera& camera,
    SceneManager &sceneManager)
{
    tbb::parallel_for(tbb::blocked_range<int>(0, height),
        [&](tbb::blocked_range<int> parallel_range)
    {
        for (int pixelY = parallel_range.begin(); pixelY < parallel_range.end(); ++pixelY)
        {
            Randomizer randEngine;

            for (int pixelX = 0; pixelX < width; ++pixelX)
            {
                int pixelIndex(pixelX + pixelY * width);
                embree::Vec3f pixelColor(0.0f);

                for (int sample = 0; sample < samples; ++sample)
                {
                    Ray primaryRay(camera, pixelX, pixelY, randEngine);

                    pixelColor += (embree::Vec3f(buffer._pixelData[pixelIndex] * (frame - 1)) +
                        integrators[integratorID]->getPixelColor(primaryRay,
                            sceneManager,
                            randEngine,
                            depth)) / (frame * (1.0f / samples));

                    // Random noise test
                    // pixelColor += (embree::Vec3f(buffer._pixelData[pixelIndex] * (frame - 1)) +
                    //     embree::Vec3f(randEngine.getRandomFloat(),
                    //     randEngine.getRandomFloat(),
                    //     randEngine.getRandomFloat())) / (frame * (1.0f / samples));
                }

                buffer._pixelData[pixelIndex] = pixelColor;
            }
        }
    });
}

void RenderManager::renderToScreenTexture(int width,
    int height,
    Buffer& buffer)
{
    glBindTexture(GL_TEXTURE_2D, screenTextureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_FLOAT, buffer._pixelData.data());

    screenQuadShader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, screenTextureID);
}

void RenderManager::cleanScreenQuad()
{
    glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
    glDeleteBuffers(1, &screenQuadVBO);

    screenQuadVBO = 0;
}

void RenderManager::drawScreenQuad()
{
    glBindVertexArray(screenQuadVAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}

bool RenderManager::setupIntegrator(int id)
{
    if (integratorID == id)
    {
        return false;    
    }

    switch(id)
    {
        case UDPT:
            integratorID = UDPT;
            break;
        case DIFFUSE:
            integratorID = DIFFUSE;
            break;
        case OCCLUSION:
            integratorID = OCCLUSION;
            break;
        case DEBUG:
            integratorID = DEBUG;
            break;
        default:
            integratorID = DEBUG;
    }

    return true;
}
