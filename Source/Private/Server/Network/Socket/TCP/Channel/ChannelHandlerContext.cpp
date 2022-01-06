// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Socket/TCP/Channel/ChannelHandlerContext.h>
#include <Server/Network/Socket/TCP/SocketPipeline.h>

namespace mpp
{
ChannelHandlerContext::ChannelHandlerContext(SocketPipeline* pipeline, const String& name, ChannelHandler* handler)
    : m_pipeline(pipeline), m_name(name), m_handler(handler)
{
}

void ChannelHandlerContext::Close()
{
    m_pipeline->m_client->m_connected = false;
}

ChannelHandlerContext* ChannelHandlerContext::FindNextInbound()
{
    ChannelHandlerContext* ctx = this;
    do
    {
        ctx = ctx->m_next;
    } while (!ctx->m_handler->IsInbound());
    return ctx;
}

ChannelHandlerContext* ChannelHandlerContext::FindNextOutbound()
{
    ChannelHandlerContext* ctx = this;
    do
    {
        ctx = ctx->m_prev;
    } while (!ctx->m_handler->IsOutbound());
    return ctx;
}

ChannelHandlerContext& ChannelHandlerContext::FireChannelRead(void* object)
{
    ChannelHandlerContext* ctx = FindNextInbound();
    if (!ctx)
    {
        MPP_LOG(LogLevel::Error, "No next handler");
        throw new std::exception();
    }
    ctx->m_handler->ChannelRead(ctx, object);
    return *this;
}

ChannelHandlerContext& ChannelHandlerContext::Write(void* object)
{
    ChannelHandlerContext* ctx = FindNextOutbound();
    if (!ctx)
    {
        MPP_LOG(LogLevel::Error, "No previous handler");
        throw new std::exception();
    }
    ctx->m_handler->Write(ctx, object);
    return *this;
}
} // namespace mpp