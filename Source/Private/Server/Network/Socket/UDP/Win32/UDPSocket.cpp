// Copyright BattleDash. All Rights Reserved.

#if defined(MPP_PLATFORM_WINDOWS)
#    include <Base/Log.h>
#    include <Server/Network/Socket/UDP/UDPSocket.h>

#    define _WINSOCKAPI_
#    include <winsock2.h>
#    include <ws2tcpip.h>

namespace mpp
{
UDPSocket::UDPSocket() : m_socket(INVALID_SOCKET)
{
}

int UDPSocket::Send(SocketAddress address, const void* data, size_t size)
{
    int sent = sendto(m_socket, (const char*)data, size, 0, (sockaddr*)address.GetAddress(), sizeof(sockaddr_in));
    if (sent == SOCKET_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to send data to client.");
        return -1;
    }

    return sent;
}

int UDPSocket::Receive(void* data, size_t size, SocketAddress& from)
{
    socklen_t fromLength = sizeof(sockaddr_in);
    sockaddr_in addr;
    int received = recvfrom(m_socket, (char*)data, size, 0, (sockaddr*)&addr, &fromLength);
    if (received == SOCKET_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to receive data from client.");
        return -1;
    }

    from.SetAddress(&addr, sizeof(sockaddr_in));

    return received;
}

bool UDPSocket::Listen(const String& ip, int port)
{
    m_socket = INVALID_SOCKET;

    if ((m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to create socket. " << WSAGetLastError());
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip.c_str());

    if (bind(m_socket, (sockaddr*)&address, sizeof(sockaddr_in)) == -1)
    {
        MPP_LOG(LogLevel::Error, "Failed to bind socket. " << WSAGetLastError());
        return false;
    }

    return true;
}

} // namespace mpp
#endif