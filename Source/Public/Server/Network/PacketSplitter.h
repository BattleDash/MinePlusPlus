// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/ServerConnection.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundHandlerAdapter.h>
#include <Server/Network/Buffer/ByteBuf.h>

namespace mpp
{
class PacketSplitter : public ChannelInboundHandlerAdapter
{
  public:
    MPP_API PacketSplitter();

    MPP_API void ChannelRead(ChannelHandlerContext* context, void* object) override;
};
} // namespace mpp