#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

#include <embree3/common/math/vec3.h>


struct Buffer
{
    Buffer();

    void Init(int width,
        int height);
    void Clean(int width,
        int height);
    void Swap(Buffer& buffer);

    std::vector<embree::Vec3f> _data;
};

#endif // BUFFER_H
