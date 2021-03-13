#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

#include <embree3/common/math/vec3.h>


struct Buffer
{
    Buffer();

    void Initialize(
        int width,
        int height);
    void Clean();
    void Clean(
        int width,
        int height);
    void Swap(
        Buffer &buffer);
    void ToPPM(
        const std::string &filename);
    void ToEXR(
        const std::string &filename);

    int width;
    int height;
    std::vector<embree::Vec3f> data;
};

#endif // BUFFER_H
