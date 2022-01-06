// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/MinecraftServer.h>
#include <Server/Network/Protocol/Handshake/PacketHandshakingInListener.h>

namespace mpp
{
class HandshakeListener : public PacketHandshakingInListener
{
  public:
    MPP_API HandshakeListener(MinecraftServer* server, NetworkManager* connection);

    MPP_API void OnDisconnect(const String& reason) override;
    MPP_API NetworkManager* GetConnection() override;

    MPP_API void HandleIntention(PacketHandshakingInSetProtocol* packet) override;

  private:
    MinecraftServer* m_server;
    NetworkManager* m_connection;
};
} // namespace mpp