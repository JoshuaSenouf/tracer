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

    frontBuffer.resize(progressiveWidth * progressiveHeight);
    backBuffer.resize(progressiveWidth * progressiveHeight);

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


std::vector<Vector3> Renderer::traceLoop(int progressiveWidth, int progressiveHeight, int progressiveSamples, int progressiveBounces, int frameCounter, std::vector<Vector3> renderBuffer)
{
    if (renderBuffer.empty() || renderBuffer == frontBuffer)
    {
        frontUsed = true;

        if (renderBuffer.empty())
            renderBuffer = getFrontBuffer();
    }

    else
        frontUsed = false;

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

    if (frontUsed)
    {
        setFrontBuffer(renderBuffer);
    }

    return renderBuffer;
}


void Renderer::renderToTexture(int textureWidth, int textureHeight, std::vector<Vector3> renderBuffer)
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


void Renderer::cleanBuffer(int bufferWidth, int bufferHeight, std::vector<Vector3> &buffer)
{
    buffer.clear();
    buffer.shrink_to_fit();
    buffer.resize(bufferWidth * bufferHeight);
}


void Renderer::displayGLBuffer()
{
    glBindVertexArray(this->quadVAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}


void Renderer::exportToPPM(int ppmWidth, int ppmHeight, std::vector<Vector3> exportBuffer)
{
    if (exportBuffer.empty())
    {
        exportBuffer = getFrontBuffer();
    }

    FILE *ppmFile = fopen("tracerRender.ppm", "w");
    fprintf(ppmFile, "P3\n%d %d\n%d\n", ppmWidth, ppmHeight, 255);

    for (int pixelIndex = 0; pixelIndex < ppmWidth * ppmHeight; ++pixelIndex)
    {
        // A lot faster than using std::ofstream or std::ostream_iterator/std::copy actually
        fprintf(ppmFile, "%d %d %d ", convertToRGB(exportBuffer[pixelIndex].x),
                convertToRGB(exportBuffer[pixelIndex].y),
                convertToRGB(exportBuffer[pixelIndex].z));
    }

    fclose(ppmFile);

    cleanBuffer(ppmWidth, ppmHeight, ppmBuffer);
}


// Based on TinyEXR way of saving scanline EXR file
void Renderer::exportToEXR(int exrWidth, int exrHeight, std::vector<Vector3> exportBuffer)
{
    if (exportBuffer.empty())
    {
        exportBuffer = getFrontBuffer();
    }

    EXRHeader exrHeader;
    EXRImage exrImage;

    InitEXRHeader(&exrHeader);
    InitEXRImage(&exrImage);

    // TODO: Make the switch to RGBA, should template the Vector class to do so conveniently
    std::vector<float> colorChannels[3];
    colorChannels[0].resize(exrWidth * exrHeight); // R channel
    colorChannels[1].resize(exrWidth * exrHeight); // G channel
    colorChannels[2].resize(exrWidth * exrHeight); // B channel

    for (int pixelIndex = 0; pixelIndex < exrWidth * exrHeight; ++pixelIndex)
    {
        colorChannels[0][pixelIndex] = exportBuffer[pixelIndex].x;
        colorChannels[1][pixelIndex] = exportBuffer[pixelIndex].y;
        colorChannels[2][pixelIndex] = exportBuffer[pixelIndex].z;
    }

    // We are swapping the channel order to BGR as many EXR file viewers are expecting this specific order,
    // such as Pixar/Renderman's "it"
    float* channelsPtr[3];
    channelsPtr[0] = &(colorChannels[2].at(0)); // B
    channelsPtr[1] = &(colorChannels[1].at(0)); // G
    channelsPtr[2] = &(colorChannels[0].at(0)); // R

    exrImage.num_channels = 3;
    exrImage.images = (unsigned char**)channelsPtr;
    exrImage.width = exrWidth;
    exrImage.height = exrHeight;

    exrHeader.num_channels = 3;
    exrHeader.channels = (EXRChannelInfo *)malloc(sizeof(EXRChannelInfo) * exrHeader.num_channels);

    strncpy(exrHeader.channels[0].name, "B", 255);
    strncpy(exrHeader.channels[1].name, "G", 255);
    strncpy(exrHeader.channels[2].name, "R", 255);
    exrHeader.channels[0].name[strlen("B")] = '\0';
    exrHeader.channels[1].name[strlen("G")] = '\0';
    exrHeader.channels[2].name[strlen("R")] = '\0';

    exrHeader.pixel_types = (int *)malloc(sizeof(int) * exrHeader.num_channels);
    exrHeader.requested_pixel_types = (int *)malloc(sizeof(int) * exrHeader.num_channels);

    for (int i = 0; i < exrHeader.num_channels; i++)
    {
        exrHeader.pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT; // Pixel type we are feeding the EXR
        exrHeader.requested_pixel_types[i] = TINYEXR_PIXELTYPE_HALF; // Pixel type we want to use as output in the EXR
    }

    const char* exrError;
    int exrResult = SaveEXRImageToFile(&exrImage, &exrHeader, "tracerRender.exr", &exrError);

    if (exrResult != TINYEXR_SUCCESS)
        fprintf(stderr, "EXR Error : %s\n", exrError);

    free(exrHeader.channels);
    free(exrHeader.pixel_types);
    free(exrHeader.requested_pixel_types);

    cleanBuffer(exrWidth, exrHeight, exrBuffer);
}


void Renderer::renderToPPM(int ppmWidth, int ppmHeight, int ppmSamples, int ppmBounces)
{
    ppmBuffer.resize(ppmWidth * ppmHeight);
    ppmBuffer = traceLoop(ppmWidth, ppmHeight, ppmSamples, ppmBounces, 1);

    exportToPPM(ppmWidth, ppmHeight, ppmBuffer);
}


void Renderer::renderToEXR(int exrWidth, int exrHeight, int exrSamples, int exrBounces)
{
    exrBuffer.resize(exrWidth * exrHeight);
    exrBuffer = traceLoop(exrWidth, exrHeight, exrSamples, exrBounces, 1);

    exportToEXR(exrWidth, exrHeight, exrBuffer);
}


void Renderer::saveToBackBuffer(int progressiveWidth, int progressiveHeight)
{
    cleanBuffer(progressiveWidth, progressiveHeight, backBuffer);

    backBuffer = frontBuffer;
}


void Renderer::swapBuffer(int progressiveWidth, int progressiveHeight)
{
    frontBuffer.swap(backBuffer);

    renderToTexture(progressiveWidth, progressiveHeight, frontBuffer);
}


std::vector<Vector3> Renderer::getFrontBuffer()
{
    return frontBuffer;
}


void Renderer::setFrontBuffer(std::vector<Vector3> buffer)
{
    frontBuffer = buffer;
}
