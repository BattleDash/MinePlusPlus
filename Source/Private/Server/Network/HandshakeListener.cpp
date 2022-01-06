// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/HandshakeListener.h>
#include <Server/Network/NetworkManager.h>
#include <Server/Network/StatusListener.h>

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
    MPP_LOG(LogLevel::Debug, "Client Protocol Version: " << packet->m_protocolVersion);
    MPP_LOG(LogLevel::Debug, "Client Host: " << packet->m_host);
    MPP_LOG(LogLevel::Debug, "Client Port: " << packet->m_port);
    MPP_LOG(LogLevel::Debug, "Client Intention: " << packet->m_intention->m_name);
    switch (packet->m_intention->m_id)
    {
    case 1:
        m_connection->SetProtocol(packet->m_intention);
        m_connection->SetListener(new StatusListener(m_server, m_connection));
        break;
    }
}
} // namespace mpp