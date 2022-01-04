// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Buffer/ByteBuf.h>

namespace mpp
{
class PacketDataSerializer
{
public:
    MPP_API PacketDataSerializer(ByteBuf* buffer);

    MPP_API int ReadVarInt();

private:
    ByteBuf* m_buffer;
};
} // namespace mpp