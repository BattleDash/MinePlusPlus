// Copyright BattleDash. All Rights Reserved.

#if defined(MPP_PLATFORM_LINUX)
#    include <Base/Log.h>
#    include <Server/Network/Socket/TCP/TCPSocketServer.h>

#    include <arpa/inet.h>
#    include <errno.h>
#    include <netdb.h>
#    include <sys/socket.h>
#    include <sys/types.h>
#    include <unistd.h>
#    include <sys/ioctl.h>
#    include <netinet/tcp.h>

#    define INVALID_SOCKET -1

namespace mpp
{
TCPSocketServer::TCPSocketServer() : m_socket(0)
{
}

TCPSocketServer::~TCPSocketServer()
{
    Close();
}

TCPSocketClient* TCPSocketServer::Accept()
{
    sockaddr clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    int clientSocket = accept(m_socket, &clientAddr, &addrSize);
    if (clientSocket == INVALID_SOCKET)
    {
        return nullptr;
    }

    return new TCPSocketClient(clientSocket, SocketAddress(&clientAddr, addrSize));
}

bool TCPSocketServer::Listen(const String& ip, int port)
{
    m_socket = INVALID_SOCKET;

    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to create socket. " << errno);
        return false;
    }

    // Turn off blocking
    u_long mode = 1;
    if (ioctl(m_socket, FIONBIO, &mode) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to set socket to non-blocking. " << errno);
        return false;
    }

    linger lin;
    lin.l_onoff = 0;
    lin.l_linger = 0;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&lin, sizeof(lin)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to set socket options. " << errno);
        return false;
    }
    
    int flag = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, sizeof(flag)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to set socket options. " << errno);
        return false;
    }

    if (setsockopt(m_socket, SOL_SOCKET, TCP_NODELAY, (const char*)&flag, sizeof(flag)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to set socket options. " << errno);
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip.c_str());

    if (bind(m_socket, (sockaddr*)&address, sizeof(sockaddr_in)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to bind socket. " << errno);
        return false;
    }

    if (listen(m_socket, SOMAXCONN) == SO_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to listen on socket. " << errno);
        return false;
    }

    MPP_LOG(LogLevel::Debug, "Bound to " << ip << ":" << port);

    return true;
}

void TCPSocketServer::Close()
{
}
} // namespace mpp
#endif