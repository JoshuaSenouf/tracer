#include "renderer.h"


Renderer::Renderer()
{

}


Renderer::~Renderer()
{
    delete accumulationBuffer;
    cleanScene();
}


void Renderer::initRender(int progressiveWidth, int progressiveHeight)
{
    quadRenderShader.setShader("res/shaders/quadRender.vert", "res/shaders/quadRender.frag");

    initQuadRender();
    initScene();

    accumulationBuffer = new Vector3[progressiveWidth * progressiveHeight];

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
    for (int y = 0; y < progressiveHeight; y++)
    {
        for (int x = 0; x < progressiveWidth; x++)
        {
            int pixelIndex = x + y * progressiveWidth;
            Vector3 radianceColor;

            for (int s = 0; s < progressiveSamples; s++)
            {
                radianceColor += (accumulationBuffer[pixelIndex] * (frameCounter - 1) + Vector3(convertToSRGB(randEngine.getRandomFloat()),
                                                                                                convertToSRGB(randEngine.getRandomFloat()),
                                                                                                convertToSRGB(randEngine.getRandomFloat()))) / frameCounter;
            }

            accumulationBuffer[pixelIndex] = radianceColor;
        }
    }

    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, progressiveWidth, progressiveHeight, GL_RGB, GL_FLOAT, accumulationBuffer);

    quadRenderShader.useShader();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);
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

    sphereCount = testScene.getSphereCount();
    spheresList = testScene.getSceneSpheresList();

//    std::cout << "SPHERECOUNT : " << sphereCount << std::endl;
//    for(int i = 0; i < sphereCount; i++)
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
    delete[] spheresList;
}


void Renderer::displayGLBuffer()
{
    glBindVertexArray(this->quadVAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}


void Renderer::renderToPPM(int ppmWidth, int ppmHeight, int ppmSamples, int ppmBounces)
{
    ppmBuffer = new Vector3[ppmWidth * ppmHeight];

    #pragma omp parallel for schedule(dynamic, 1)
    for (int y = 0; y < ppmHeight; y++)
    {
        for (int x = 0; x < ppmWidth; x++)
        {
            Vector3 radianceColor;

            for (int s = 0; s < ppmSamples; s++)
            {
                radianceColor += Vector3(randEngine.getRandomFloat(), randEngine.getRandomFloat(), randEngine.getRandomFloat()) * (1.0f / ppmSamples);
            }

            ppmBuffer[(ppmHeight - y - 1) * ppmWidth + x] += radianceColor;
        }
    }

    FILE *f = fopen("tracerRender.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", ppmWidth, ppmHeight, 255);

    for (int i = 0; i < ppmWidth * ppmHeight; i++)
    {
        fprintf(f, "%d %d %d ", convertToRGB(ppmBuffer[i].x), convertToRGB(ppmBuffer[i].y), convertToRGB(ppmBuffer[i].z));
    }

    fclose(f);

    delete ppmBuffer;
}


inline float Renderer::clamp(float x)
{
    return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}


inline float Renderer::convertToSRGB(float x)
{
    return pow(x, 1.0f / 2.2f);
}

inline float Renderer::convertToLinear(float x)
{
    return pow(x, 2.2f);
}

inline int Renderer::convertToRGB(float x)
{
    return int(convertToSRGB(clamp(x)) * 255);
}

