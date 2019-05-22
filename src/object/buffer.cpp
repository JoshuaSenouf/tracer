#include "buffer.h"


Buffer::Buffer()
{

}

void Buffer::init(int width,
    int height)
{
    _pixelData.resize(width * height);
}

void Buffer::clean(int width,
    int height)
{
    _pixelData.clear();
    _pixelData.shrink_to_fit();
    _pixelData.resize(width * height);
}

void Buffer::swap(Buffer& buffer)
{
    _pixelData.swap(buffer._pixelData);
}
