// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/HandshakeListener.h>
#include <Server/Network/Protocol/Handshake/PacketHandshakingInSetProtocol.h>

namespace mpp
{
HandshakeListener::HandshakeListener(MinecraftServer* server, NetworkManager* connection)
    : m_server(server), m_connection(connection)
{
}

void HandshakeListener::OnDisconnect(const String& reason)
{
    MPP_LOG(LogLevel::Info, "Disconnected from server: " << reason);
}

NetworkManager* HandshakeListener::GetConnection()
{
    return m_connection;
}

void HandshakeListener::HandleIntention(PacketHandshakingInSetProtocol* packet)
{
    MPP_LOG(LogLevel::Debug, "[PacketHandshakingInSetProtocol] Client Protocol Version: " << packet->m_protocolVersion);
    MPP_LOG(LogLevel::Debug, "[PacketHandshakingInSetProtocol] Client Host: " << packet->m_host);
    MPP_LOG(LogLevel::Debug, "[PacketHandshakingInSetProtocol] Client Port: " << packet->m_port);
    MPP_LOG(LogLevel::Debug, "[PacketHandshakingInSetProtocol] Client Intention: " << packet->m_intention->m_id);
}
} // namespace mpp