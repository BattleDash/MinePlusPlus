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
        ConnectionProtocol* protocol = context->m_pipeline->m_client->Attr<ConnectionProtocol>("protocol");
        if (protocol != nullptr)
        {
            PacketWrapper* packetWrapper = protocol->GetPacketWrapper(m_direction, packetId);
            if (packetWrapper != nullptr)
            {
                MPP_LOG(LogLevel::Debug, "Deserializing packet " << packetWrapper->name);
                void* packet = packetWrapper->ctor(&packetDataSerializer);
                context->FireChannelRead(packet);
                delete reinterpret_cast<Packet<void>*>(packet);
                if (packetDataSerializer.IsReadable())
                {
                    MPP_LOG(LogLevel::Error, "Packet " << packetWrapper->name << " has " << packetDataSerializer.ReadableBytes()
                                                      << " bytes left in the serializer");
                }
            }
            else
            {
                MPP_LOG(LogLevel::Error, "Unknown packet id " << packetId);
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