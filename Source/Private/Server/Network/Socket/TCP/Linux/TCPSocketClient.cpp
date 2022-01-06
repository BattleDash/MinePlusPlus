// Copyright BattleDash. All Rights Reserved.

#if defined(MPP_PLATFORM_LINUX)
#    include <Base/Log.h>
#    include <Server/Network/Socket/TCP/TCPSocketClient.h>

#    include <arpa/inet.h>
#    include <errno.h>
#    include <netdb.h>
#    include <sys/socket.h>
#    include <sys/types.h>
#    include <unistd.h>

namespace mpp
{
TCPSocketClient::TCPSocketClient(int socket, SocketAddress address)
    : m_socket(socket), m_address(address), m_pipeline(new SocketPipeline(this)), m_connected(true)
{
}

TCPSocketClient::~TCPSocketClient()
{
    Close();
    delete m_pipeline;
}

int TCPSocketClient::Send(const void* data, size_t size)
{
    int sent = send(m_socket, (const char*)data, size, 0);
    if (sent == SO_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to send data to client.");
        return -1;
    }

    return sent;
}

int TCPSocketClient::Receive(void* data, size_t size)
{
    int received = recv(m_socket, (char*)data, size, 0);
    if (received == SO_ERROR)
    {
        if (errno == EWOULDBLOCK)
        {
            return -2;
        }
        else
        {
            MPP_LOG(LogLevel::Error, "Failed to receive data from client. " << errno);
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