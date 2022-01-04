// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Server/Network/Buffer/UnpooledDirectByteBuf.h>

namespace mpp
{
class Unpooled
{
public:
    static ByteBuf* WrapBuffer(void* data, size_t size)
    {
        UnpooledDirectByteBuf* buffer = new UnpooledDirectByteBuf(0, size);
        buffer->WriteBytes(data, 0, size);
        return buffer;
    }
};
} // namespace mpp