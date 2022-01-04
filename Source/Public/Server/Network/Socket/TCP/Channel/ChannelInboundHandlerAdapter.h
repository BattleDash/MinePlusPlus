// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundhandler.h>

namespace mpp
{
class ChannelInboundHandlerAdapter : public ChannelInboundHandler
{
  public:
    MPP_API void ChannelRegistered() override;
    MPP_API void ChannelUnregistered() override;
    MPP_API void ChannelActive() override;
    MPP_API void ChannelInactive() override;
    MPP_API void ChannelRead(void* object) override;
    MPP_API void ChannelReadComplete() override;
    MPP_API void UserEventTriggered(void* object) override;
    MPP_API void ChannelWritabilityChanged() override;
    MPP_API void ExceptionCaught(void* object) override;
};
} // namespace mpp