// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/Protocol/Handshake/PacketHandshakingInListener.h>
#include <Server/Network/Protocol/Packet.h>

namespace mpp
{
class ConnectionProtocol;
class PacketHandshakingInListener;

class PacketHandshakingInSetProtocol : public Packet<PacketHandshakingInListener>
{
  public:
    MPP_API PacketHandshakingInSetProtocol(const String& host, int port, ConnectionProtocol* protocol);
    MPP_API PacketHandshakingInSetProtocol(PacketDataSerializer* serializer);
    MPP_API ~PacketHandshakingInSetProtocol();

    MPP_API void Write(PacketDataSerializer* serializer) override;
    MPP_API void Handle(PacketHandshakingInListener* listener) override;

    int m_protocolVersion;
    String m_host;
    int m_port;
    ConnectionProtocol* m_intention;
};

MPP_DECLARE_PACKET_TYPE(PacketHandshakingInSetProtocol)
} // namespace mpp