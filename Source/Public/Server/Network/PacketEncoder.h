// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/ServerConnection.h>
#include <Server/Network/Socket/TCP/Channel/ChannelOutboundHandlerAdapter.h>
#include <Server/Network/Buffer/ByteBuf.h>
#include <Server/Network/Protocol/EProtocolDirection.h>

namespace mpp
{
class PacketEncoder : public ChannelOutboundHandlerAdapter
{
  public:
    MPP_API PacketEncoder(EProtocolDirection direction);

    MPP_API void Write(ChannelHandlerContext* context, void* object) override;

  private:
    EProtocolDirection m_direction;
};
} // namespace mpp