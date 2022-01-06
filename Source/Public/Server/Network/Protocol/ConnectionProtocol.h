// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>
#include <Server/Network/Protocol/EProtocolDirection.h>
#include <Server/Network/Protocol/Packet.h>

#include <functional>

namespace mpp
{
class ConnectionProtocol
{
  public:
    MPP_API ConnectionProtocol(int id, const String& name, PacketFlow* flows, int flowCount);

    MPP_API PacketWrapper* GetPacketWrapper(EProtocolDirection direction, int id);
    MPP_API int GetPacketId(const String& packetName);
    MPP_API int GetPacketId(Packet<void>* packet);

    MPP_API static ConnectionProtocol* RegisterProtocol(int id, const String& name, PacketFlow* flows, int flowCount);
    MPP_API static ConnectionProtocol* GetProtocol(int id);
    MPP_API static void Initialize();

    int m_id;
    String m_name;
    PacketFlow* m_flows;
    int m_flowCount;

    static std::vector<ConnectionProtocol*> s_protocols;
};

#define MPP_REGISTER_PROTOCOL(id, name, flowTable)                                                                     \
    ConnectionProtocol::RegisterProtocol(id, name, s_packet_flow_##flowTable,                                          \
                                         sizeof(s_packet_flow_##flowTable) / sizeof(mpp::PacketFlow))
} // namespace mpp