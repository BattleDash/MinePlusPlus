// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>

namespace mpp
{
class ChannelInboundHandler
{
  public:
    MPP_API virtual void ChannelRegistered() = 0;
    MPP_API virtual void ChannelUnregistered() = 0;
    MPP_API virtual void ChannelActive() = 0;
    MPP_API virtual void ChannelInactive() = 0;
    MPP_API virtual void ChannelIdle() = 0;
    MPP_API virtual void ChannelRead(void* object) = 0;
    MPP_API virtual void ChannelReadComplete() = 0;
    MPP_API virtual void UserEventTriggered(void* object) = 0;
    MPP_API virtual void ChannelWritabilityChanged() = 0;
    MPP_API virtual void ExceptionCaught(void* object) = 0;
};
} // namespace mpp