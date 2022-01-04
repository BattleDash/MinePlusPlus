// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/ServerConnection.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundHandlerAdapter.h>
#include <Server/Network/Buffer/ByteBuf.h>
#include <Server/Network/Protocol/EProtocolDirection.h>

namespace mpp
{
class PacketDecoder : public ChannelInboundHandlerAdapter
{
  public:
    MPP_API PacketDecoder(EProtocolDirection direction);

    MPP_API void ChannelRead(ChannelHandlerContext* context, void* object) override;

  private:
    EProtocolDirection m_direction;
};
} // namespace mpp