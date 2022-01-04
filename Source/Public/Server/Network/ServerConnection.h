// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/MinecraftServer.h>

namespace mpp
{
class MinecraftServer;

class ServerConnection
{
  public:
    MPP_API ServerConnection(MinecraftServer* server);

    MPP_API void StartTCPServer(String host, int port);
  private:
    MinecraftServer* m_server;
    bool m_running;
};
} // namespace mpp