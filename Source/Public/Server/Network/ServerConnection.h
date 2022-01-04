// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/MinecraftServer.h>
#include <Server/Network/Socket/TCP/TCPSocketManager.h>

namespace mpp
{
class MinecraftServer;

class ServerConnection
{
  public:
    MPP_API ServerConnection(MinecraftServer* server);
    MPP_API ~ServerConnection();

    MPP_API void StartTCPServer(String host, int port);
  private:
    MinecraftServer* m_server;
    TCPSocketManager* m_socketManager;
};
} // namespace mpp