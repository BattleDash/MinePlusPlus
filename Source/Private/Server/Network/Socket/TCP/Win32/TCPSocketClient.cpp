// Copyright BattleDash. All Rights Reserved.

#if defined(MPP_PLATFORM_WINDOWS)
#    include <Base/Log.h>
#    include <Server/Network/Socket/TCP/TCPSocketClient.h>

#    define _WINSOCKAPI_
#    include <winsock2.h>
#    include <ws2tcpip.h>

#    pragma comment(lib, "Ws2_32.lib")

namespace mpp
{
TCPSocketClient::TCPSocketClient(int socket, SocketAddress address)
    : m_socket(socket), m_address(address), m_pipeline(new SocketPipeline(this)), m_connected(true)
{
    // Turn off blocking
    u_long mode = 1;
    if (ioctlsocket(m_socket, FIONBIO, &mode) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to set socket to non-blocking. " << WSAGetLastError());
    }
}

TCPSocketClient::~TCPSocketClient()
{
    Close();
    delete m_pipeline;
}

int TCPSocketClient::Send(const void* data, size_t size)
{
    int sent = send(m_socket, (const char*)data, size, 0);
    if (sent == SOCKET_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to send data to client.");
        return -1;
    }

    MPP_LOG(LogLevel::Debug, "Sent " << sent << " bytes to client.");

    return sent;
}

int TCPSocketClient::Receive(void* data, size_t size)
{
    int received = recv(m_socket, (char*)data, size, 0);
    if (received == SOCKET_ERROR)
    {
        int code = WSAGetLastError();
        if (code == WSAEWOULDBLOCK)
        {
            return -2;
        }
        else
        {
            MPP_LOG(LogLevel::Error, "Failed to receive data from client. " << code);
            return -1;
        }
    }

    return received;
}

void TCPSocketClient::Close()
{
    closesocket(m_socket);
}
} // namespace mpp
#endif