// Copyright BattleDash. All Rights Reserved.

#include <Server/Network/Socket/TCP/Channel/ChannelHandlerContext.h>

namespace mpp
{
ChannelHandlerContext::ChannelHandlerContext(SocketPipeline* socket, const String& name, ChannelHandler* handler)
    : m_socket(socket), m_name(name), m_handler(handler)
{
}

ChannelHandlerContext& ChannelHandlerContext::FireChannelRead(void* object)
{
    return *this;
}
} // namespace mpp