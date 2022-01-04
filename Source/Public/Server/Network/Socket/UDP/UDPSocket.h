// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/SocketAddress.h>

namespace mpp
{
class UDPSocket
{
  public:
    MPP_API UDPSocket();

    MPP_API int Send(SocketAddress address, const void* data, size_t size);
    MPP_API int Receive(void* data, size_t size, SocketAddress& from);
    MPP_API bool Listen(const String& ip, int port);

  private:
    int m_socket;
};
} // namespace mpp