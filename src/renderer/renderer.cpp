#include "renderer.h"


Renderer::Renderer()
{
    
}


void Renderer::initRender(int renderWidth, int renderHeight)
{
    quadRenderShader.setShader("res/shaders/quadRender.vert", "res/shaders/quadRender.frag");

    initQuadRender();
    initScene();

    outputBuffer = new glm::vec3[renderWidth * renderHeight];
}


void Renderer::renderTracer(int renderWidth, int renderHeight, int renderSamples, int renderBounces)
{
    std::uniform_real_distribution<float> randURF(-2147483648, 2147483647);
//    std::uniform_real_distribution<float> randURF(0, 255);

    quadRenderShader.useShader();

    for (int y = 0; y < renderHeight; y++)
    {
        for (int x = 0; x < renderWidth; x++)
        {
            int pixelIndex = (renderHeight - y - 1) * renderWidth + x;

            // RENDER CODE

//            outputBuffer[pixelIndex] = glm::vec3(randURF(randSeed), randURF(randSeed), randURF(randSeed));
        }
    }
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
    glm::vec3* ppmBuffer = new glm::vec3[renderWidth * renderHeight];

    std::uniform_real_distribution<float> randURF(LONG_MIN, LONG_MAX);
//    std::uniform_real_distribution<float> randURF(0, 255);

    for (int y = 0; y < renderHeight; y++)
    {
        for (int x = 0; x < renderWidth; x++)
        {
            int pixelIndex = (renderHeight - y - 1) * renderWidth + x;

            ppmBuffer[pixelIndex] = glm::vec3(randURF(randSeed), randURF(randSeed), randURF(randSeed));
        }
    }

    FILE *f = fopen("tracerRender.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", renderWidth, renderHeight, 255);

    for (int i = 0; i < renderWidth * renderHeight; i++)
    {
        fprintf(f, "%d %d %d ", hdrToSRGB(ppmBuffer[i].x), hdrToSRGB(ppmBuffer[i].y), hdrToSRGB(ppmBuffer[i].z));
    }

    fclose(f);
}


inline float Renderer::clamp(float x)
{
    return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}


inline int Renderer::hdrToSRGB(float x)
{
    return int(pow(clamp(x), 1 / 2.2) * 255);
}
