// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>

namespace mpp
{
enum class ChannelHandlerType
{
  Inbound,
  Outbound
};

class ChannelHandler
{
  public:
    MPP_API virtual ChannelHandlerType Type() = 0;
};
} // namespace mpp