// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Socket/TCP/SocketPipeline.h>

namespace mpp
{
HeadContext::HeadContext(SocketPipeline* pipeline)
    : ChannelHandlerContext(pipeline, "mpp_internal_pipeline_head", this), ChannelInboundHandlerAdapter()
{
}

HeadContext::~HeadContext()
{
}

TailContext::TailContext(SocketPipeline* pipeline)
    : ChannelHandlerContext(pipeline, "mpp_internal_pipeline_tail", this), ChannelInboundHandlerAdapter()
{
}

void TailContext::ChannelRead(ChannelHandlerContext* context, void* object)
{
}

SocketPipeline::SocketPipeline(TCPSocketClient* client)
    : m_client(client), m_head(new HeadContext(this)), m_tail(new TailContext(this))
{
    m_head->m_next = m_tail;
    m_tail->m_prev = m_head;
}

SocketPipeline::~SocketPipeline()
{
    delete m_head;
}

SocketPipeline* SocketPipeline::AddLast(const String& name, ChannelHandler* handler)
{
    MPP_ASSERT(handler != nullptr);

    ChannelHandlerContext* newCtx = new ChannelHandlerContext(this, name, handler);
    ChannelHandlerContext* prev = m_tail->m_prev;
    newCtx->m_prev = prev;
    newCtx->m_next = m_tail;
    prev->m_next = newCtx;
    m_tail->m_prev = newCtx;

    return this;
}

ChannelHandlerContext* SocketPipeline::Get(const String& name)
{
    ChannelHandlerContext* ctx = m_head->m_next;
    while (ctx != m_tail)
    {
        if (ctx->m_name == name)
        {
            return ctx;
        }
        ctx = ctx->m_next;
    }
    return nullptr;
}

void SocketPipeline::Remove(const String& name)
{
    ChannelHandlerContext* ctx = Get(name);
    MPP_ASSERT(ctx != nullptr);
    MPP_ASSERT(ctx != m_head && ctx != m_tail);

    ChannelHandlerContext* prev = ctx->m_prev;
    ChannelHandlerContext* next = ctx->m_next;
    prev->m_next = next;
    next->m_prev = prev;
}

const String SocketPipeline::ToString()
{
    String string = "";
    ChannelHandlerContext* ctx = m_head->m_next;
    while (ctx != m_tail)
    {
        string += ctx->m_name;
        ctx = ctx->m_next;
        if (ctx != m_tail)
        {
            string += " -> ";
        }
    }
    return string;
}
} // namespace mpp