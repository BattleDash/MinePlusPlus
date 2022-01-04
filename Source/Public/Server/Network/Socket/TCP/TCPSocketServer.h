// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Server/Network/Socket/TCP/TCPSocketClient.h>

namespace mpp
{
class TCPSocketServer
{
  public:
    MPP_API TCPSocketServer();
    MPP_API ~TCPSocketServer();

    MPP_API bool Listen(const String& ip, int port);
    MPP_API TCPSocketClient* Accept();
    MPP_API void Close();

  private:
    int m_socket;
};
} // namespace mpp