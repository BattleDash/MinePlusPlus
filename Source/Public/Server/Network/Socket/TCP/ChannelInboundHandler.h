// Copyright BattleDash. All Rights Reserved.

#include <Base/Platform.h>

namespace mpp
{
class ChannelInboundHandler
{
  public:
    MPP_API virtual void ChannelRegistered();
    MPP_API virtual void ChannelUnregistered();
    MPP_API virtual void ChannelActive();
    MPP_API virtual void ChannelInactive();
    MPP_API virtual void ChannelRead(void* object);
    MPP_API virtual void ChannelReadComplete();
    MPP_API virtual void UserEventTriggered(void* object);
    MPP_API virtual void ChannelWritabilityChanged();
    MPP_API virtual void ExceptionCaught(void* object);
};
} // namespace mpp