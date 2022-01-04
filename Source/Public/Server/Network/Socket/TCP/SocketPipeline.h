// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundHandler.h>

#include <vector>

namespace mpp
{
class SocketPipeline
{
  public:
    MPP_API SocketPipeline();
    MPP_API ~SocketPipeline();

    MPP_API SocketPipeline* AddLast(String name, ChannelInboundHandler* handler);
    MPP_API std::vector<std::pair<String, ChannelInboundHandler*>>& Handlers();
    MPP_API void Remove(String name);

  private:
    std::vector<std::pair<String, ChannelInboundHandler*>> m_handlers;
};
} // namespace mpp