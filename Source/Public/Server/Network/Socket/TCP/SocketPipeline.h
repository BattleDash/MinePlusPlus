// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/TCP/TCPSocketClient.h>
#include <Server/Network/Socket/TCP/Channel/ChannelHandlerContext.h>
#include <Server/Network/Socket/TCP/Channel/ChannelHandlerAdapter.h>

#include <vector>

namespace mpp
{
class HeadContext : public ChannelHandlerContext, public ChannelHandlerAdapter
{
public:
    MPP_API HeadContext(SocketPipeline* pipeline);
    MPP_API ~HeadContext();

    MPP_API void Write(ChannelHandlerContext* context, void* object) override;
};

class TailContext : public ChannelHandlerContext, public ChannelHandlerAdapter
{
public:
    MPP_API TailContext(SocketPipeline* pipeline);

    MPP_API void ChannelRead(ChannelHandlerContext* context, void* object) override;
};

class TCPSocketClient;

class SocketPipeline
{
  public:
    MPP_API SocketPipeline(TCPSocketClient* client);
    MPP_API ~SocketPipeline();

    MPP_API SocketPipeline* AddLast(const String& name, ChannelHandler* handler);
    
    MPP_API ChannelHandlerContext* Get(const String& name);
    MPP_API void Remove(const String& name);
    MPP_API const String ToString();

    TCPSocketClient* m_client;
    ChannelHandlerContext* m_head;
    ChannelHandlerContext* m_tail;
};
} // namespace mpp