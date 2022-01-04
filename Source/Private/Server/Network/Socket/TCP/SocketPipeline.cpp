// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Socket/TCP/SocketPipeline.h>

namespace mpp
{
SocketPipeline::SocketPipeline()
{
}

SocketPipeline::~SocketPipeline()
{
    for (auto it = m_handlers.begin(); it != m_handlers.end();)
    {
        std::pair<String, ChannelHandler*> pair = *it;
        delete pair.second;
        it = m_handlers.erase(it);
    }
}

SocketPipeline* SocketPipeline::AddLast(String name, ChannelHandler* handler)
{
    if (Get(name) != nullptr)
    {
        MPP_LOG(LogLevel::Error, "Channel already exists");
        return this;
    }
    m_handlers.push_back(std::make_pair(name, handler));
    return this;
}

ChannelHandler* SocketPipeline::Get(String name)
{
    for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
    {
        if (it->first == name)
        {
            return it->second;
        }
    }
    return nullptr;
}

std::vector<std::pair<String, ChannelHandler*>>& SocketPipeline::Handlers()
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