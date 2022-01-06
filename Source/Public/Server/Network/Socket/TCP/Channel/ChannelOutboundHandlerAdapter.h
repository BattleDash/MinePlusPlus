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
    MPP_API void ChannelRegistered(ChannelHandlerContext* context) override
    {
    }
    MPP_API void ChannelUnregistered(ChannelHandlerContext* context) override
    {
    }
    MPP_API void ChannelActive(ChannelHandlerContext* context) override
    {
    }
    MPP_API void ChannelInactive(ChannelHandlerContext* context) override
    {
    }
    MPP_API void ChannelIdle(ChannelHandlerContext* context) override
    {
    }
    MPP_API void ChannelRead(ChannelHandlerContext* context, void* object) override
    {
    }
    MPP_API void ChannelReadComplete(ChannelHandlerContext* context) override
    {
    }
    MPP_API void UserEventTriggered(ChannelHandlerContext* context, void* object) override
    {
    }
    MPP_API void ChannelWritabilityChanged(ChannelHandlerContext* context) override
    {
    }
    MPP_API void ExceptionCaught(ChannelHandlerContext* context, void* object) override
    {
    }
    MPP_API void Write(ChannelHandlerContext* context, void* object) override
    {
        context->Write(object);
    }
};
} // namespace mpp