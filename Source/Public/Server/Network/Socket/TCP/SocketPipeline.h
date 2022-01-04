// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/TCP/Channel/ChannelHandler.h>

#include <vector>

namespace mpp
{
class SocketPipeline
{
  public:
    MPP_API SocketPipeline();
    MPP_API ~SocketPipeline();

    MPP_API SocketPipeline* AddLast(String name, ChannelHandler* handler);
    MPP_API ChannelHandler* Get(String name);
    MPP_API std::vector<std::pair<String, ChannelHandler*>>& Handlers();
    MPP_API void Remove(String name);

  private:
    std::vector<std::pair<String, ChannelHandler*>> m_handlers;
};
} // namespace mpp