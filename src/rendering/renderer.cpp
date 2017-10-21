#include "renderer.h"


Renderer::Renderer()
{

}


Renderer::~Renderer()
{

}


void Renderer::initRender(int progressiveWidth, int progressiveHeight)
{
    quadRenderShader.setShader("res/shaders/quadRender.vert", "res/shaders/quadRender.frag");

    initQuadRender();
    initScene();

    glGenTextures(1, &this->renderTextureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);

    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, progressiveWidth, progressiveHeight);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}


void Renderer::initQuadRender()
{
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);
}


void Renderer::initScene()
{
//    Scene testScene;
//    testScene.loadScene("res/scenes/testScene.txt");

//    spheresList = testScene.getSceneSpheresList();
//    sphereCount = spheresList.size();

//    std::cout << "SPHERECOUNT : " << sphereCount << std::endl;
//    for(int i = 0; i < sphereCount; ++i)
//    {
//        std::cout << "RADIUS : " << spheresList[i].radius << std::endl;
//        std::cout << "POS X : " << spheresList[i].position.x << " POS Y : " << spheresList[i].position.y << " POS Z : " << spheresList[i].position.z << std::endl;
//        std::cout << "COL R : " << spheresList[i].color.x << " COL G : " << spheresList[i].color.y << " COL B: " << spheresList[i].color.z << std::endl;
//        std::cout << "EMI R : " << spheresList[i].emissiveColor.x << " EMI G : " << spheresList[i].emissiveColor.y << " EMI B : " << spheresList[i].emissiveColor.z << std::endl;
//        std::cout << "///////////////" << std::endl;
//    }
}


void Renderer::traceLoop(int progressiveWidth, int progressiveHeight, int progressiveSamples, int progressiveBounces, int frameCounter, std::vector<Vector3>& renderBuffer)
{
#pragma omp parallel for schedule(dynamic, 1)
    for (int pixelY = 0; pixelY < progressiveHeight; ++pixelY)
    {
        Randomizer randEngine;

        for (int pixelX = 0; pixelX < progressiveWidth; ++pixelX)
        {
            int pixelIndex = pixelX + pixelY * progressiveWidth;
            Vector3 radianceColor;

            for (int sample = 0; sample < progressiveSamples; ++sample)
            {
                radianceColor += (renderBuffer[pixelIndex] * (frameCounter - 1) + Vector3(convertToSRGB(randEngine.getRandomFloat()),
                                                                                          convertToSRGB(randEngine.getRandomFloat()),
                                                                                          convertToSRGB(randEngine.getRandomFloat()))) / frameCounter * (1.0f / progressiveSamples);
            }

            renderBuffer[pixelIndex] = radianceColor;
        }
    }
}


void Renderer::renderToTexture(int textureWidth, int textureHeight, const std::vector<Vector3>& renderBuffer)
{
    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGB, GL_FLOAT, renderBuffer.data());

    quadRenderShader.useShader();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);
}


void Renderer::cleanQuadRender()
{
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glDeleteBuffers(1, &quadVBO);

    quadVBO = 0;
}


void Renderer::cleanScene()
{
    sphereCount = 0;

    spheresList.clear();
    spheresList.shrink_to_fit();
}


void Renderer::displayGLBuffer()
{
    glBindVertexArray(this->quadVAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}
