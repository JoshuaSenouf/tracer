#include "render_helper.h"

#include "buffer.h"


Buffer::Buffer()
{

}


void Buffer::initBuffer(int bufferWidth,
    int bufferHeight)
{
    bufferData.resize(bufferWidth * bufferHeight);
}


void Buffer::cleanBufferData(int bufferWidth,
    int bufferHeight)
{
    bufferData.clear();
    bufferData.shrink_to_fit();
    bufferData.resize(bufferWidth * bufferHeight);
}


void Buffer::swapBufferData(std::vector<Vector3>& buffer)
{
    bufferData.swap(buffer);
}


std::vector<Vector3>& Buffer::getBufferData()
{
    return bufferData;
}


void Buffer::setBufferData(const std::vector<Vector3>& buffer)
{
    bufferData = buffer;
}


void exportToPPM(int ppmWidth,
    int ppmHeight,
    const std::vector<Vector3>& exportBuffer)
{
    FILE *ppmFile = fopen("tracerRender.ppm", "w");
    fprintf(ppmFile, "P3\n%d %d\n%d\n", ppmWidth, ppmHeight, 255);

    for (int pixelIndex = 0; pixelIndex < ppmWidth * ppmHeight; ++pixelIndex)
    {
        // A lot faster than using std::ofstream or std::ostream_iterator/std::copy actually
        fprintf(ppmFile, "%d %d %d ", convertToRGB(convertToSRGB(exportBuffer[pixelIndex].x)),
                convertToRGB(convertToSRGB(exportBuffer[pixelIndex].y)),
                convertToRGB(convertToSRGB(exportBuffer[pixelIndex].z)));
    }

    fclose(ppmFile);
}


// Based on TinyEXR way of saving scanline EXR file
void exportToEXR(int exrWidth,
    int exrHeight,
    const std::vector<Vector3>& exportBuffer)
{
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

    std::strncpy(exrHeader.channels[0].name, "B", 255);
    std::strncpy(exrHeader.channels[1].name, "G", 255);
    std::strncpy(exrHeader.channels[2].name, "R", 255);
    exrHeader.channels[0].name[std::strlen("B")] = '\0';
    exrHeader.channels[1].name[std::strlen("G")] = '\0';
    exrHeader.channels[2].name[std::strlen("R")] = '\0';

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
        fprintf(stderr, "EXR Error: %s\n", exrError);

    free(exrHeader.channels);
    free(exrHeader.pixel_types);
    free(exrHeader.requested_pixel_types);
}
