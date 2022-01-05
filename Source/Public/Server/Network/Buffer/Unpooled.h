// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Server/Network/Buffer/UnpooledDirectByteBuf.h>

namespace mpp
{
class Unpooled
{
public:
    static ByteBuf* WrapArray(void* data, size_t size)
    {
        UnpooledDirectByteBuf* buffer = new UnpooledDirectByteBuf(size, size);
        buffer->WriterIndex(0);
        buffer->WriteBytes(data, 0, size);
        return buffer;
    }
    static ByteBuf* Buffer()
    {
        ByteBuf* byteBuf = new UnpooledDirectByteBuf(512, 2147483647);
        byteBuf->WriterIndex(0);
        return byteBuf;
    }
};
} // namespace mpp