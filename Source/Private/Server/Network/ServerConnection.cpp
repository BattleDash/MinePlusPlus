// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/ServerConnection.h>
#include <Server/Network/Socket/TCP/TCPSocketManager.h>

namespace mpp
{
ServerConnection::ServerConnection(MinecraftServer* server) : m_server(server), m_running(false)
{
}

void ServerConnection::StartTCPServer(String host, int port)
{
    MPP_LOG(LogLevel::Info, "Starting TCP Server...");

    
}
} // namespace mpp