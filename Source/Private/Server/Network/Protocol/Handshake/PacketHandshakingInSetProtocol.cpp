// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/Protocol/Handshake/PacketHandshakingInSetProtocol.h>

namespace mpp
{
PacketHandshakingInSetProtocol::PacketHandshakingInSetProtocol(PacketDataSerializer* serializer)
{
    m_protocolVersion = serializer->ReadVarInt();
    m_host = serializer->ReadUtf();
    m_port = serializer->ReadUnsignedShort();
    m_intention = ConnectionProtocol::GetProtocol(serializer->ReadVarInt());
}

void PacketHandshakingInSetProtocol::Write(PacketDataSerializer* serializer)
{
}

void PacketHandshakingInSetProtocol::Handle(PacketHandshakingInListener* listener)
{
    listener->HandleIntention(this);
}
} // namespace mpp