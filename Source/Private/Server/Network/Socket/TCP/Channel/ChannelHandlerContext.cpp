// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Socket/TCP/Channel/ChannelHandlerContext.h>

namespace mpp
{
ChannelHandlerContext::ChannelHandlerContext(SocketPipeline* pipeline, const String& name, ChannelHandler* handler)
    : m_pipeline(pipeline), m_name(name), m_handler(handler)
{
}

ChannelHandlerContext& ChannelHandlerContext::FireChannelRead(void* object)
{
    if (!m_next)
    {
        MPP_LOG(LogLevel::Error, "No next handler");
        throw new std::exception();
    }
    MPP_LOG(LogLevel::Debug, "Executing " << m_next->m_name << " from " << m_name);
    m_next->m_handler->ChannelRead(m_next, object);
    return *this;
}
} // namespace mpp