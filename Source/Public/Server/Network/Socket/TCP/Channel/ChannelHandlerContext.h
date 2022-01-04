// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/TCP/SocketPipeline.h>
#include <Server/Network/Socket/TCP/Channel/ChannelHandler.h>

namespace mpp
{
class ChannelHandlerContext
{
  public:
    MPP_API ChannelHandlerContext(SocketPipeline* socket, const String& name, ChannelHandler* handler);

    MPP_API virtual ChannelHandlerContext& FireChannelRead(void* object) = 0;

    SocketPipeline* m_socket;
    String m_name;
    ChannelHandler* m_handler;
};
} // namespace mpp