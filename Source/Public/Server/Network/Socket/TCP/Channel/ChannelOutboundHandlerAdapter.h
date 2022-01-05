// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Socket/TCP/Channel/ChannelOutboundHandler.h>

namespace mpp
{
class ChannelOutboundHandlerAdapter : public ChannelOutboundHandler
{
  public:
    MPP_API bool IsInbound() override
    {
        return false;
    }
    MPP_API bool IsOutbound() override
    {
        return true;
    }
    MPP_API void Write(ChannelHandlerContext* context, void* object) override
    {
        context->Write(object);
    }
};
} // namespace mpp