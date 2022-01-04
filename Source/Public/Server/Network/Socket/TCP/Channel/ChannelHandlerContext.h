// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/TCP/Channel/ChannelHandler.h>

namespace mpp
{
class SocketPipeline;

class ChannelHandlerContext
{
  public:
    MPP_API ChannelHandlerContext(SocketPipeline* pipeline, const String& name, ChannelHandler* handler);

    MPP_API ChannelHandlerContext& FireChannelRead(void* object);

    ChannelHandlerContext* m_next;
    ChannelHandlerContext* m_prev;

    SocketPipeline* m_pipeline;
    String m_name;
    ChannelHandler* m_handler;
};
} // namespace mpp