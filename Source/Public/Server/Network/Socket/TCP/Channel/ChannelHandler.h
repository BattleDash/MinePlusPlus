// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>

namespace mpp
{
class ChannelHandlerContext;

class ChannelHandler
{
  public:
    MPP_API virtual bool IsInbound() = 0;
    MPP_API virtual bool IsOutbound() = 0;

    MPP_API virtual void ChannelRegistered(ChannelHandlerContext* context) = 0;
    MPP_API virtual void ChannelUnregistered(ChannelHandlerContext* context) = 0;
    MPP_API virtual void ChannelActive(ChannelHandlerContext* context) = 0;
    MPP_API virtual void ChannelInactive(ChannelHandlerContext* context) = 0;
    MPP_API virtual void ChannelIdle(ChannelHandlerContext* context) = 0;
    MPP_API virtual void ChannelRead(ChannelHandlerContext* context, void* object) = 0;
    MPP_API virtual void ChannelReadComplete(ChannelHandlerContext* context) = 0;
    MPP_API virtual void UserEventTriggered(ChannelHandlerContext* context, void* object) = 0;
    MPP_API virtual void ChannelWritabilityChanged(ChannelHandlerContext* context) = 0;
    MPP_API virtual void ExceptionCaught(ChannelHandlerContext* context, void* object) = 0;

    MPP_API virtual void Write(ChannelHandlerContext* context, void* object) = 0;
};
} // namespace mpp