// Copyright BattleDash. All Rights Reserved.

#pragma once

#if defined(MPP_PLATFORM_WINDOWS)
#    define _WINSOCKAPI_

#    include <Base/Log.h>
#    include <Server/Network/Socket/TCP/TCPSocketClient.h>

#    include <Windows.h>
#    include <winsock2.h>
#    include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace mpp
{
TCPSocketClient::TCPSocketClient(int socket) : m_socket(socket)
{
}

TCPSocketClient::~TCPSocketClient()
{
    Close();
}

int TCPSocketClient::Send(const void* data, size_t size)
{
    int sent = send(m_socket, (const char*)data, size, 0);
    if (sent == SOCKET_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to send data to client.");
        return -1;
    }

    return sent;
}

int TCPSocketClient::Receive(void* data, size_t size)
{
    int received = recv(m_socket, (char*)data, size, 0);
    if (received == SOCKET_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to receive data from client.");
        return -1;
    }

    return received;
}

void TCPSocketClient::Close()
{
}
} // namespace mpp
#endif