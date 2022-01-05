// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>
#include <Server/Network/PacketDecoder.h>

namespace mpp
{
PacketDecoder::PacketDecoder(EProtocolDirection direction) : m_direction(direction)
{
}

void PacketDecoder::ChannelRead(ChannelHandlerContext* context, void* object)
{
    ByteBuf* byteBuf = static_cast<ByteBuf*>(object);
    int readableBytes = byteBuf->ReadableBytes();
    if (readableBytes != 0)
    {
        PacketDataSerializer packetDataSerializer(byteBuf);
        int packetId = packetDataSerializer.ReadVarInt();
        MPP_LOG(LogLevel::Debug, "Received packet with id " << packetId);
        
        context->FireChannelRead(static_cast<void*>(byteBuf));
    }
    else
    {
        MPP_LOG(LogLevel::Debug, "Received empty packet");
    }
}
} // namespace mpp