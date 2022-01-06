// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundHandlerAdapter.h>

namespace mpp
{
template <typename I> class SimpleChannelInboundHandler : public ChannelInboundHandlerAdapter
{
  public:
    MPP_API void ChannelRead(ChannelHandlerContext* context, void* object) override
    {
        ChannelRead0(context, object);
    }
    MPP_API void ChannelRead0(ChannelHandlerContext* context, I* object)
    {
        context->FireChannelRead(object);
    }
};
} // namespace mpp