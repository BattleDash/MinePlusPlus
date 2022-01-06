// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>
#include <Server/Network/Protocol/EProtocolDirection.h>
#include <Server/Network/Protocol/Handshake/PacketHandshakingInSetProtocol.h>
#include <Server/Network/Protocol/Packet.h>

#include <functional>

namespace mpp
{
class ConnectionProtocol
{
  public:
    MPP_API ConnectionProtocol(int id, PacketFlow* flows, int flowCount);

    MPP_API PacketWrapper* GetPacketWrapper(EProtocolDirection direction, int id);

    MPP_API static ConnectionProtocol* RegisterProtocol(int id, PacketFlow* flows, int flowCount);
    MPP_API static ConnectionProtocol* GetProtocol(int id);
    MPP_API static void Initialize();
    
    int m_id;
    PacketFlow* m_flows;
    int m_flowCount;

    static std::vector<ConnectionProtocol*> s_protocols;
};

#define MPP_REGISTER_PROTOCOL(id, flowTable) \
    ConnectionProtocol::RegisterProtocol(id, s_packet_flow_##flowTable, sizeof(s_packet_flow_##flowTable) / sizeof(mpp::PacketFlow))
} // namespace mpp