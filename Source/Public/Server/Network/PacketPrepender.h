// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Socket/TCP/Channel/ChannelOutboundHandlerAdapter.h>

namespace mpp
{
class PacketPrepender : public ChannelOutboundHandlerAdapter
{
  public:
    MPP_API void Write(ChannelHandlerContext* context, void* object) override;
};
} // namespace mpp