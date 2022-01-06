// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>
#include <Server/Network/PacketDecoder.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>

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
        ConnectionProtocol* protocol = context->m_pipeline->m_client->Attr<ConnectionProtocol>("protocol");
        if (protocol != nullptr)
        {
            PacketWrapper* packetWrapper = protocol->GetPacketWrapper(m_direction, packetId);
            if (packetWrapper != nullptr)
            {
                context->FireChannelRead(static_cast<void*>(packetWrapper->ctor(&packetDataSerializer)));
            }
        }
        else
        {
            MPP_LOG(LogLevel::Error, "Protocol not set");
        }
    }
    else
    {
        MPP_LOG(LogLevel::Debug, "Received empty packet");
    }
}
} // namespace mpp