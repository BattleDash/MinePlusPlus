// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/ServerConnection.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundHandlerAdapter.h>
#include <Server/Network/Buffer/ByteBuf.h>

namespace mpp
{
class LegacyPingHandler : public ChannelInboundHandlerAdapter
{
  public:
    MPP_API LegacyPingHandler(ServerConnection* serverConnection);

    MPP_API ByteBuf* CreateReply(const WideString& data);
    MPP_API void SendAndClose(ChannelHandlerContext* context, ByteBuf* byteBuf);
    MPP_API bool AttemptHandlePingPacket(ChannelHandlerContext* context, ByteBuf* byteBuf);
    MPP_API void ChannelRead(ChannelHandlerContext* context, void* object) override;

  private:
    ServerConnection* m_serverConnection;
};
} // namespace mpp