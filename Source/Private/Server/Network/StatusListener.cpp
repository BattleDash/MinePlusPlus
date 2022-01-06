// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/StatusListener.h>
#include <Server/Network/NetworkManager.h>
#include <Server/Network/Protocol/Status/PacketStatusOutServerInfo.h>
#include <Server/Network/Protocol/Status/PacketStatusOutPong.h>

namespace mpp
{
StatusListener::StatusListener(MinecraftServer* server, NetworkManager* connection)
    : m_server(server), m_connection(connection)
{
}

void StatusListener::OnDisconnect(const String& reason)
{
    MPP_LOG(LogLevel::Info, "Disconnected from server: " << reason);
}

NetworkManager* StatusListener::GetConnection()
{
    return m_connection;
}

void StatusListener::HandleStatusRequest(PacketStatusInStart* packet)
{
    m_connection->Send(new PacketStatusOutServerInfo());
}

void StatusListener::HandlePingRequest(PacketStatusInPing* packet)
{
    m_connection->Send(new PacketStatusOutPong(packet->m_time));
}
} // namespace mpp