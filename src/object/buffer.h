#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>

#include "vector.h"


struct Buffer
{
    Buffer();

    void init(int width,
        int height);
    void clean(int width,
        int height);
    void swap(Buffer& buffer);

    std::vector<Vector3> _pixelData;
};

#endif // BUFFER_H
