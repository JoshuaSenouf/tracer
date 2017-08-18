#include "renderer.h"


Renderer::Renderer()
{
    
}


Renderer::~Renderer()
{
    delete accumulationBuffer;
    cleanScene();
}


void Renderer::initRender(int renderWidth, int renderHeight)
{
    quadRenderShader.setShader("res/shaders/quadRender.vert", "res/shaders/quadRender.frag");

    initQuadRender();
    initScene();

    accumulationBuffer = new Vector3[renderWidth * renderHeight];

    glGenTextures(1, &this->renderTextureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderWidth, renderHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, accumulationBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}


void Renderer::renderTracer(int renderWidth, int renderHeight, int renderSamples, int renderBounces)
{
    std::uniform_real_distribution<float> randURF(0, 1);

    #pragma omp parallel for schedule(dynamic, 1)
    for (int y = 0; y < renderHeight; y++)
    {
        for (int x = 0; x < renderWidth; x++)
        {
            Vector3 radianceColor;

            for (int s = 0; s < renderSamples; s++)
            {
                radianceColor += Vector3(randURF(randSeed), randURF(randSeed), randURF(randSeed)) * (1.0 / renderSamples);
            }

            accumulationBuffer[x + y * renderWidth] += radianceColor;
        }
    }

    glBindTexture(GL_TEXTURE_2D, this->renderTextureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, renderWidth, renderHeight, GL_RGB, GL_UNSIGNED_BYTE, accumulationBuffer);

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


void Renderer::renderToPPM(int renderWidth, int renderHeight, int renderSamples, int renderBounces)
{
    ppmBuffer = new Vector3[renderWidth * renderHeight];

    std::uniform_real_distribution<float> randURF(0, 1);

    #pragma omp parallel for schedule(dynamic, 1)
    for (int y = 0; y < renderHeight; y++)
    {
        for (int x = 0; x < renderWidth; x++)
        {
            Vector3 radianceColor;

            for (int s = 0; s < renderSamples; s++)
            {
                radianceColor += Vector3(randURF(randSeed), randURF(randSeed), randURF(randSeed)) * (1.0 / renderSamples);
            }

            ppmBuffer[(renderHeight - y - 1) * renderWidth + x] += radianceColor;
        }
    }

    FILE *f = fopen("tracerRender.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", renderWidth, renderHeight, 255);

    for (int i = 0; i < renderWidth * renderHeight; i++)
    {
        fprintf(f, "%d %d %d ", hdrToSRGB(ppmBuffer[i].x), hdrToSRGB(ppmBuffer[i].y), hdrToSRGB(ppmBuffer[i].z));
    }

    fclose(f);

    delete ppmBuffer;
}


inline float Renderer::clamp(float x)
{
    return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}


inline int Renderer::hdrToSRGB(float x)
{
    return int(pow(clamp(x), 1 / 2.2) * 255);
}
