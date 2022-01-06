// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>

namespace mpp
{
std::vector<ConnectionProtocol*> ConnectionProtocol::s_protocols;

ConnectionProtocol::ConnectionProtocol(int id, PacketFlow* flows, int flowCount) : m_id(id), m_flows(flows), m_flowCount(flowCount)
{
    MPP_LOG(LogLevel::Info, "id: " << id << ", flowCount: " << flowCount);
}

PacketWrapper* ConnectionProtocol::GetPacketWrapper(EProtocolDirection direction, int id)
{
    // Find the flow with the direction
    PacketFlow* flow = nullptr;
    for (int i = 0; i < m_flowCount; i++)
    {
        if (m_flows[i].direction == direction)
        {
            flow = &m_flows[i];
            break;
        }
    }

    // Find the packet in the flow
    if (flow != nullptr)
    {
        for (int i = 0; i < flow->count; i++)
        {
            if (i == id)
            {
                return &flow->packets[i];
            }
        }
    }

    return nullptr;
}

MPP_BEGIN_PACKET_TABLE(ServerboundHandshakePackets)
MPP_PACKET(PacketHandshakingInSetProtocol)
MPP_END_PACKET_TABLE()

MPP_BEGIN_PROTOCOL(HANDSHAKE)
MPP_PROTOCOL_FLOW(EProtocolDirection::SERVERBOUND, ServerboundHandshakePackets)
MPP_END_PROTOCOL()

void ConnectionProtocol::Initialize()
{
    MPP_REGISTER_PROTOCOL(-1, HANDSHAKE);
}

ConnectionProtocol* ConnectionProtocol::RegisterProtocol(int id, PacketFlow* flows, int flowCount)
{
    ConnectionProtocol* protocol = new ConnectionProtocol(id, flows, flowCount);
    s_protocols.push_back(protocol);
    return protocol;
}

ConnectionProtocol* ConnectionProtocol::GetProtocol(int id)
{
    for (int i = 0; i < s_protocols.size(); i++)
    {
        if (s_protocols[i]->m_id == id)
        {
            return s_protocols[i];
        }
    }
    return nullptr;
}
} // namespace mpp