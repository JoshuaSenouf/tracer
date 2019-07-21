#include "rendermanager.h"


RenderManager::RenderManager()
{
}

void RenderManager::Trace(const RenderGlobals& renderGlobals,
    SceneManager &sceneManager,
    Camera& camera,
    Buffer& buffer,
    int iterations)
{
    tbb::parallel_for(tbb::blocked_range<int>(0, renderGlobals.height),
        [&](tbb::blocked_range<int> height_range)
    {
        for (int pixelY = height_range.begin(); pixelY < height_range.end(); ++pixelY)
        {
            Sampler sampler;

            for (int pixelX = 0; pixelX < renderGlobals.width; ++pixelX)
            {
                // We setup all the necessary data describing the current sample.
                PixelSample pixelSample(sampler);
                pixelSample.pixelX = pixelX;
                pixelSample.pixelY = pixelY;
                pixelSample.pixelIdx = pixelX + pixelY * renderGlobals.width;
                pixelSample.samples = renderGlobals.samples;
                pixelSample.sampleIdx = 0;

                // The final pixel color of the sample we are computed that will be added and averaged to the buffer.
                embree::Vec3f pixelColor(0.0f);

                for (int sample = 0; sample < renderGlobals.samples; ++sample)
                {
                    Ray primaryRay(camera, pixelSample);

                    pixelColor += (embree::Vec3f(buffer._pixelData[pixelSample.pixelIdx] * (iterations - 1)) +
                        integrators[renderGlobals.integratorID]->GetPixelColor(primaryRay,
                            pixelSample,
                            sceneManager,
                            renderGlobals)) * (1.0f / renderGlobals.samples);

                    // Random noise test
                    // pixelColor += (embree::Vec3f(buffer._pixelData[pixelSample.pixelIdx] * (iterations - 1)) +
                    //     embree::Vec3f(pixelSample.sampler.Uniform1D(),
                    //         pixelSample.sampler.Uniform1D(),
                    //         pixelSample.sampler.Uniform1D())) * (1.0f / renderGlobals.samples);

                    pixelSample.sampleIdx++;
                }

                buffer._pixelData[pixelSample.pixelIdx] = pixelColor / iterations;
            }
        }
    });
}

void RenderManager::RenderToScreenTexture(int width,
    int height,
    Buffer& buffer)
{
    glBindTexture(GL_TEXTURE_2D, screenTextureID);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_FLOAT, buffer._pixelData.data());
    screenQuadShader.Use();
    glActiveTexture(GL_TEXTURE0);
    
    glBindTexture(GL_TEXTURE_2D, screenTextureID);
}

void RenderManager::SetupScreenQuad(int width,
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
    screenQuadShader.Setup("res/shaders/screenQuad.vert",
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

void RenderManager::CleanScreenQuad()
{
    glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
    glDeleteBuffers(1, &screenQuadVBO);

    screenQuadVBO = 0;
}

void RenderManager::DrawScreenQuad()
{
    glBindVertexArray(screenQuadVAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}
