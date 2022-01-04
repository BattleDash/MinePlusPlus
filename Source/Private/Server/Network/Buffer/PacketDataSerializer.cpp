// Copyright BattleDash. All Rights Reserved.

#include <Server/Network/Buffer/PacketDataSerializer.h>

#include <stdexcept>

namespace mpp
{
PacketDataSerializer::PacketDataSerializer(ByteBuf* buffer) : m_buffer(buffer)
{
}

int PacketDataSerializer::ReadVarInt()
{
    int value = 0;
    int shift = 0;
    uint8_t b;
    do
    {
        b = m_buffer->ReadByte();
        value |= (b & 127) << shift++ * 7;
        if (shift > 5)
        {
            throw std::runtime_error("VarInt too big");
        }
    } while ((b & 128) == 128);
    return value;
}
} // namespace mpp