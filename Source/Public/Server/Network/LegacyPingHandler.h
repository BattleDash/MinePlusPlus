// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/ServerConnection.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundHandlerAdapter.h>

namespace mpp
{
class LegacyPingHandler : public ChannelInboundHandlerAdapter
{
  public:
    MPP_API LegacyPingHandler(ServerConnection* serverConnection);
    MPP_API ~LegacyPingHandler();

    MPP_API void ChannelRead(void* object) override;

  private:
    ServerConnection* m_serverConnection;
};
} // namespace mpp