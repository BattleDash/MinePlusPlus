// Copyright BattleDash. All Rights Reserved.

#include <Server/Network/Socket/TCP/SocketPipeline.h>

namespace mpp
{
SocketPipeline::SocketPipeline()
{
}

SocketPipeline::~SocketPipeline()
{
}

SocketPipeline* SocketPipeline::AddLast(String name, ChannelInboundHandler* handler)
{
    m_handlers.push_back(std::make_pair(name, handler));
    return this;
}

std::vector<std::pair<String, ChannelInboundHandler*>>& SocketPipeline::Handlers()
{
    return m_handlers;
}

void SocketPipeline::Remove(String name)
{
    for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
    {
        if (it->first == name)
        {
            m_handlers.erase(it);
            break;
        }
    }
}
} // namespace mpp