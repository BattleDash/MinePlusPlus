// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

#include <Server/Network/Socket/TCP/SocketPipeline.h>

#include <map>

namespace mpp
{
class TCPSocketClient
{
  public:
    MPP_API TCPSocketClient(int socket);
    MPP_API ~TCPSocketClient();

    MPP_API int Send(const void* data, size_t size);
    MPP_API int Receive(void* data, size_t size);
    MPP_API void Close();

    MPP_API SocketPipeline* Pipeline()
    {
        return m_pipeline;
    }
    template <typename T> MPP_API T* Attr(const String& key)
    {
        auto it = m_attributes.find(key);
        if (it == m_attributes.end())
        {
            return nullptr;
        }

        return (T*)it->second;
    }
    template <typename T> MPP_API void Attr(const String& key, T* value)
    {
        m_attributes[key] = value;
    }
    template <typename T> MPP_API bool HasAttr(const String& key)
    {
        return m_attributes.find(key) != m_attributes.end();
    }

    bool m_connected;

  private:
    SocketPipeline* m_pipeline;
    std::map<String, void*> m_attributes;
    int m_socket;
};
} // namespace mpp