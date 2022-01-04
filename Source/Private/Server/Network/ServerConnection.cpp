// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/ServerConnection.h>

#if defined(MPP_PLATFORM_WINDOWS)
#    include <Windows.h>
#elif defined(MPP_PLATFORM_LINUX)
#    include <arpa/inet.h>
#    include <netinet/in.h>
#    include <sys/socket.h>
#endif

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