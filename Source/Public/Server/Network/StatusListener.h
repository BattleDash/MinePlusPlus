// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/MinecraftServer.h>
#include <Server/Network/Protocol/Status/PacketStatusInListener.h>

namespace mpp
{
class StatusListener : public PacketStatusInListener
{
  public:
    MPP_API StatusListener(MinecraftServer* server, NetworkManager* connection);

    MPP_API void OnDisconnect(const String& reason) override;
    MPP_API NetworkManager* GetConnection() override;

    MPP_API void HandleStatusRequest(PacketStatusInStart* packet) override;
    MPP_API void HandlePingRequest(PacketStatusInPing* packet) override;

  private:
    MinecraftServer* m_server;
    NetworkManager* m_connection;
};
} // namespace mpp