// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

#include <Server/Network/Socket/TCP/SocketPipeline.h>

namespace mpp
{
class TCPSocketClient
{
  public:
    MPP_API TCPSocketClient(int socket);
    MPP_API ~TCPSocketClient();

    MPP_API int Send(const void* data, size_t size);
    MPP_API int Receive(void* data, size_t size);
    MPP_API SocketPipeline* Pipeline();
    MPP_API void Close();

    bool m_connected;
  private:
    SocketPipeline* m_pipeline;
    int m_socket;
};
} // namespace mpp