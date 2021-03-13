#include <spdlog/spdlog.h>

#define TINYEXR_IMPLEMENTATION

#include <tinyexr.h>

#include "utility/color.h"

#include "object/buffer.h"


Buffer::Buffer()
{
    spdlog::trace("Buffer::Buffer()");
}

void Buffer::Initialize(
    int width,
    int height)
{
    spdlog::trace("Buffer::Initialize()");

    this->width = width;
    this->height = height;

    data.resize(this->width * this->height);

    spdlog::debug(
        "Buffer::Initialize() - "
        "Buffer initialized successfully.");
}

void Buffer::Clean()
{
    spdlog::trace("Buffer::Clean()");

    data.clear();
    data.shrink_to_fit();
    data.resize(width * height);

    spdlog::debug(
        "Buffer::Clean() - "
        "Buffer cleaned successfully.");
}

void Buffer::Clean(
    int width,
    int height)
{
    spdlog::trace("Buffer::Clean()");

    data.clear();
    data.shrink_to_fit();
    data.resize(width * height);

    spdlog::debug(
        "Buffer::Clean() - "
        "Buffer cleaned successfully.");
}

void Buffer::Swap(
    Buffer &buffer)
{
    spdlog::trace("Buffer::Swap()");

    data.swap(buffer.data);

    spdlog::debug(
        "Buffer::Swap() - "
        "Buffer swapped successfully.");
}

void Buffer::ToPPM(
    const std::string &filename)
{
    spdlog::trace("ToPPM()");

    FILE *ppm_file(fopen(filename.c_str(), "w"));
    fprintf(ppm_file, "P3\n%d %d\n%d\n", width, height, 255);

    for (unsigned int pixel_idx = 0; pixel_idx < (width * height); ++pixel_idx)
    {
        // A lot faster than using std::ofstream or std::ostream_iterator/std::copy, actually.
        fprintf(ppm_file, "%d %d %d ",
            ToRGB(LinearToSRGB(data[pixel_idx].x)),
            ToRGB(LinearToSRGB(data[pixel_idx].y)),
            ToRGB(LinearToSRGB(data[pixel_idx].z)));
    }

    fclose(ppm_file);

    spdlog::info(
        "ToPPM() - "
        "Render exported to PPM successfully.");
}

// Based on TinyEXR way of saving a scanline EXR file.
void Buffer::ToEXR(
    const std::string &filename)
{
    spdlog::trace("ToEXR()");

    EXRHeader exr_header;
    EXRImage exr_image;

    InitEXRHeader(&exr_header);
    InitEXRImage(&exr_image);

    // TODO: Make the switch to RGBA, should template the Vector class to do so conveniently.
    std::vector<float> channels[3];
    channels[0].resize(width * height); // R channel
    channels[1].resize(width * height); // G channel
    channels[2].resize(width * height); // B channel

    for (unsigned int pixel_idx = 0; pixel_idx < (width * height); ++pixel_idx)
    {
        channels[0][pixel_idx] = data[pixel_idx].x;
        channels[1][pixel_idx] = data[pixel_idx].y;
        channels[2][pixel_idx] = data[pixel_idx].z;
    }

    // We are swapping the channel order to BGR as many EXR file viewers are expecting this specific order,
    // such as Pixar/Renderman's "it".
    float *channels_ptr[3];
    channels_ptr[0] = &(channels[2].at(0)); // B
    channels_ptr[1] = &(channels[1].at(0)); // G
    channels_ptr[2] = &(channels[0].at(0)); // R

    exr_image.num_channels = 3;
    exr_image.images = (unsigned char**)channels_ptr;
    exr_image.width = width;
    exr_image.height = height;

    exr_header.num_channels = 3;
    exr_header.channels = (EXRChannelInfo *)malloc(sizeof(EXRChannelInfo) * exr_header.num_channels);

    std::strncpy(exr_header.channels[0].name, "B", 255);
    std::strncpy(exr_header.channels[1].name, "G", 255);
    std::strncpy(exr_header.channels[2].name, "R", 255);
    exr_header.channels[0].name[std::strlen("B")] = '\0';
    exr_header.channels[1].name[std::strlen("G")] = '\0';
    exr_header.channels[2].name[std::strlen("R")] = '\0';

    exr_header.pixel_types = (int *)malloc(sizeof(int) * exr_header.num_channels);
    exr_header.requested_pixel_types = (int *)malloc(sizeof(int) * exr_header.num_channels);

    for (unsigned int channel_idx = 0; channel_idx < exr_header.num_channels; ++channel_idx)
    {
        // Pixel type we are feeding the EXR
        exr_header.pixel_types[channel_idx] = TINYEXR_PIXELTYPE_FLOAT;
        // Pixel type we want to use as output in the EXR
        exr_header.requested_pixel_types[channel_idx] = TINYEXR_PIXELTYPE_HALF;
    }

    const char* exr_error;
    int exr_result(SaveEXRImageToFile(&exr_image, &exr_header, filename.c_str(), &exr_error));

    if (exr_result != TINYEXR_SUCCESS)
    {
        fprintf(stderr, "EXR Error: %s\n", exr_error);
    }

    free(exr_header.channels);
    free(exr_header.pixel_types);
    free(exr_header.requested_pixel_types);

    spdlog::info(
        "ToEXR() - "
        "Render exported to EXR successfully.");
}
