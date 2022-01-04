// Copyright BattleDash. All Rights Reserved.

#if defined(MPP_PLATFORM_LINUX)
#    include <Base/Log.h>
#    include <Server/Network/Socket/TCP/TCPSocketClient.h>

#    include <arpa/inet.h>
#    include <netinet/in.h>
#    include <sys/socket.h>

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