// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/Protocol/Handshake/PacketHandshakingInSetProtocol.h>
#include <Server/Network/Protocol/Status/PacketStatusInPing.h>
#include <Server/Network/Protocol/Status/PacketStatusInStart.h>
#include <Server/Network/Protocol/Status/PacketStatusOutServerInfo.h>
#include <Server/Network/Protocol/Status/PacketStatusOutPong.h>

namespace mpp
{
std::vector<ConnectionProtocol*> ConnectionProtocol::s_protocols;

ConnectionProtocol::ConnectionProtocol(int id, const String& name, PacketFlow* flows, int flowCount)
    : m_id(id), m_name(name), m_flows(flows), m_flowCount(flowCount)
{
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

MPP_BEGIN_PACKET_TABLE(ServerboundStatusPackets)
MPP_PACKET(PacketStatusInStart)
MPP_PACKET(PacketStatusInPing)
MPP_END_PACKET_TABLE()

MPP_BEGIN_PACKET_TABLE(ClientboundStatusPackets)
MPP_PACKET(PacketStatusOutServerInfo)
MPP_PACKET(PacketStatusOutPong)
MPP_END_PACKET_TABLE()

MPP_BEGIN_PROTOCOL(HandshakeProtocol)
MPP_PROTOCOL_FLOW(EProtocolDirection::SERVERBOUND, ServerboundHandshakePackets)
MPP_END_PROTOCOL()

MPP_BEGIN_PROTOCOL(StatusProtocol)
MPP_PROTOCOL_FLOW(EProtocolDirection::SERVERBOUND, ServerboundStatusPackets)
MPP_PROTOCOL_FLOW(EProtocolDirection::CLIENTBOUND, ClientboundStatusPackets)
MPP_END_PROTOCOL()

void ConnectionProtocol::Initialize()
{
    MPP_REGISTER_PROTOCOL(-1, "Handshake", HandshakeProtocol);
    MPP_REGISTER_PROTOCOL(0, "Play", HandshakeProtocol);
    MPP_REGISTER_PROTOCOL(1, "Status", StatusProtocol);
    MPP_REGISTER_PROTOCOL(2, "Login", HandshakeProtocol);
}

ConnectionProtocol* ConnectionProtocol::RegisterProtocol(int id, const String& name, PacketFlow* flows, int flowCount)
{
    for (auto& protocol : s_protocols)
    {
        if (protocol->m_id == id)
        {
            s_protocols.erase(std::remove(s_protocols.begin(), s_protocols.end(), protocol), s_protocols.end());
            break;
        }
    }
    ConnectionProtocol* protocol = new ConnectionProtocol(id, name, flows, flowCount);
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

int ConnectionProtocol::GetPacketId(const String& packetName)
{
    for (int i = 0; i < m_flowCount; i++)
    {
        for (int j = 0; j < m_flows[i].count; j++)
        {
            if (m_flows[i].packets[j].name == packetName)
            {
                return j;
            }
        }
    }
    return -1;
}

int ConnectionProtocol::GetPacketId(Packet<void>* packet)
{
    return GetPacketId(packet->Name());
}
} // namespace mpp