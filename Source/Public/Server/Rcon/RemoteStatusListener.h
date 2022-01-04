// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Socket/UDP/UDPSocket.h>
#include <Server/MinecraftServer.h>

#include <thread>

namespace mpp
{
class RemoteStatusListener
{
  public:
    MPP_API RemoteStatusListener(MinecraftServer* server, const String& host, int port);
    MPP_API ~RemoteStatusListener();

  private:
    MPP_API void Run();
    MPP_API void ProcessPacket(SocketAddress& from, void* data, size_t size);

    MinecraftServer* m_server;
    UDPSocket* m_socket;
    std::thread m_thread;
};
} // namespace mpp