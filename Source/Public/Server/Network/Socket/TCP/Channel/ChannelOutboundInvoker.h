// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>

namespace mpp
{
class ChannelOutboundInvoker
{
  public:
    MPP_API virtual ChannelOutboundInvoker& Write(void* object) = 0;
};
} // namespace mpp