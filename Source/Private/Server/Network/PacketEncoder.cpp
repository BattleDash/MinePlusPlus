// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>
#include <Server/Network/Buffer/Unpooled.h>
#include <Server/Network/PacketEncoder.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>

namespace mpp
{
PacketEncoder::PacketEncoder(EProtocolDirection direction) : m_direction(direction)
{
}

void PacketEncoder::Write(ChannelHandlerContext* context, void* object)
{
    Packet<void>* packet = static_cast<Packet<void>*>(object);
    ConnectionProtocol* protocol = context->m_pipeline->m_client->Attr<ConnectionProtocol>("protocol");
    if (protocol == nullptr)
    {
        throw new std::runtime_error("ConnectionProtocol unknown for packet '" + packet->Name() + "'");
    }
    int id = protocol->GetPacketId(packet);
    if (id == -1)
    {
        throw new std::runtime_error("Packet '" + packet->Name() + "' invalid");
    }
    MPP_LOG(LogLevel::Debug,
            "Sending packet with id " << id << " (" << packet->Name() << "), using protocol " << protocol->m_name);
    ByteBuf* buffer = Unpooled::Buffer();
    PacketDataSerializer serializer(buffer);
    serializer.WriteVarInt(id);
    int writerIndex = serializer.WriterIndex();
    packet->Write(&serializer);
    int length = serializer.WriterIndex() - writerIndex;
    if (length > 8388608)
    {
        throw new std::runtime_error("Packet too big, max size is 8388608 bytes");
    }
    context->Write(buffer);
}
} // namespace mpp