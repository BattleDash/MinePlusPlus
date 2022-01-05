// Copyright BattleDash. All Rights Reserved.

#if defined(MPP_PLATFORM_WINDOWS)
#    include <Base/Log.h>
#    include <Server/Network/Socket/TCP/TCPSocketServer.h>

#    define _WINSOCKAPI_
#    include <winsock2.h>
#    include <ws2tcpip.h>

#    pragma comment(lib, "Ws2_32.lib")

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
    // Accept and get client addr
    sockaddr clientAddr;
    int addrSize = sizeof(clientAddr);
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
        MPP_LOG(LogLevel::Error, "Failed to create socket. " << WSAGetLastError());
        return false;
    }

    // Turn off blocking
    u_long mode = 1;
    if (ioctlsocket(m_socket, FIONBIO, &mode) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to set socket to non-blocking. " << WSAGetLastError());
        return false;
    }

    linger lin;
    lin.l_onoff = 0;
    lin.l_linger = 0;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&lin, sizeof(lin)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to set socket options. " << WSAGetLastError());
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip.c_str());

    if (bind(m_socket, (sockaddr*)&address, sizeof(sockaddr_in)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to bind socket. " << WSAGetLastError());
        return false;
    }

    if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to listen on socket. " << WSAGetLastError());
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