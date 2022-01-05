// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/TCP/Channel/ChannelHandler.h>
#include <Server/Network/Socket/TCP/Channel/ChannelOutboundInvoker.h>

namespace mpp
{
class SocketPipeline;

class ChannelHandlerContext : public ChannelOutboundInvoker
{
  public:
    MPP_API ChannelHandlerContext(SocketPipeline* pipeline, const String& name, ChannelHandler* handler);

    MPP_API ChannelHandlerContext& FireChannelRead(void* object);
    MPP_API ChannelHandlerContext& Write(void* object) override;
    MPP_API ChannelHandlerContext* FindNextInbound();
    MPP_API ChannelHandlerContext* FindNextOutbound();
    MPP_API void Close();

    ChannelHandlerContext* m_next;
    ChannelHandlerContext* m_prev;

    SocketPipeline* m_pipeline;
    String m_name;
    ChannelHandler* m_handler;
};
} // namespace mpp