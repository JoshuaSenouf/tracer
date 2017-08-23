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

    accumulationBuffer.resize(progressiveWidth * progressiveHeight);

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


void Renderer::renderTracer(int progressiveWidth, int progressiveHeight, int progressiveSamples, int progressiveBounces, int frameCounter)
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
                radianceColor += (accumulationBuffer[pixelIndex] * (frameCounter - 1) + Vector3(convertToSRGB(randEngine.getRandomFloat()),
                                                                                                convertToSRGB(randEngine.getRandomFloat()),
                                                                                                convertToSRGB(randEngine.getRandomFloat()))) / frameCounter * (1.0f / progressiveSamples);
            }

            accumulationBuffer[pixelIndex] = radianceColor;
        }
    }

    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, progressiveWidth, progressiveHeight, GL_RGB, GL_FLOAT, accumulationBuffer.data());

    quadRenderShader.useShader();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);
}


void Renderer::cleanAccumulationBuffer(int progressiveWidth, int progressiveHeight)
{
    accumulationBuffer.clear();
    accumulationBuffer.shrink_to_fit();
    accumulationBuffer.resize(progressiveWidth * progressiveHeight);
}


void Renderer::cleanPPMBuffer()
{
    ppmBuffer.clear();
    ppmBuffer.shrink_to_fit();
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


void Renderer::cleanQuadRender()
{
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glDeleteBuffers(1, &quadVBO);

    quadVBO = 0;
}


void Renderer::initScene()
{
    Scene testScene;
    testScene.loadScene("res/scenes/testScene.txt");

    spheresList = testScene.getSceneSpheresList();
    sphereCount = spheresList.size();

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


void Renderer::exportToPPM(int ppmWidth, int ppmHeight)
{
    FILE *ppmFile = fopen("tracerExport.ppm", "w");
    fprintf(ppmFile, "P3\n%d %d\n%d\n", ppmWidth, ppmHeight, 255);

    for (int pixelIndex = 0; pixelIndex < ppmWidth * ppmHeight; ++pixelIndex)
    {
        // A lot faster than using std::ofstream or std::ostream_iterator/std::copy actually
        fprintf(ppmFile, "%d %d %d ",   convertToRGB(accumulationBuffer[pixelIndex].x),
                                        convertToRGB(accumulationBuffer[pixelIndex].y),
                                        convertToRGB(accumulationBuffer[pixelIndex].z));
    }

    fclose(ppmFile);
}


void Renderer::renderToPPM(int ppmWidth, int ppmHeight, int ppmSamples, int ppmBounces)
{
    ppmBuffer.resize(ppmWidth * ppmHeight);

    #pragma omp parallel for schedule(dynamic, 1)
    for (int pixelY = 0; pixelY < ppmHeight; ++pixelY)
    {
        Randomizer randEngine;

        for (int pixelX = 0; pixelX < ppmWidth; ++pixelX)
        {
            int pixelIndex = pixelX + pixelY * ppmWidth;
            Vector3 radianceColor;

            for (int sample = 0; sample < ppmSamples; ++sample)
            {
                radianceColor += Vector3(convertToSRGB(randEngine.getRandomFloat()),
                                         convertToSRGB(randEngine.getRandomFloat()),
                                         convertToSRGB(randEngine.getRandomFloat())) * (1.0f / ppmSamples);
            }

            ppmBuffer[pixelIndex] += radianceColor;
        }
    }

    FILE *ppmFile = fopen("tracerRender.ppm", "w");
    fprintf(ppmFile, "P3\n%d %d\n%d\n", ppmWidth, ppmHeight, 255);

    for (int pixelIndex = 0; pixelIndex < ppmWidth * ppmHeight; ++pixelIndex)
    {
        fprintf(ppmFile, "%d %d %d ",   convertToRGB(ppmBuffer[pixelIndex].x),
                                        convertToRGB(ppmBuffer[pixelIndex].y),
                                        convertToRGB(ppmBuffer[pixelIndex].z));
    }

    fclose(ppmFile);

    cleanPPMBuffer();
}
