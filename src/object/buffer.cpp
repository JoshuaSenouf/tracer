#include "buffer.h"


Buffer::Buffer()
{
    spdlog::trace("Buffer::Buffer()");
}

void Buffer::Init(int width,
    int height)
{
    spdlog::trace("Buffer::Init()");

    _data.resize(width * height);

    spdlog::info("Buffer::Init() - "
        "Buffer initialized successfully.");
}

void Buffer::Clean(int width,
    int height)
{
    spdlog::trace("Buffer::Clean()");

    _data.clear();
    _data.shrink_to_fit();
    _data.resize(width * height);

    spdlog::debug("Buffer::Clean() - "
        "Buffer cleaned successfully.");
}

void Buffer::Swap(Buffer& buffer)
{
    spdlog::trace("Buffer::Swap()");

    _data.swap(buffer._data);

    spdlog::debug("Buffer::Swap() - "
        "Buffer swapped successfully.");
}
