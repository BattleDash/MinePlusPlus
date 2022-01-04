// Copyright BattleDash. All Rights Reserved.

#if defined(MPP_PLATFORM_LINUX)
#    include <Base/Log.h>
#    include <Server/Network/Socket/UDP/UDPSocket.h>

#    include <arpa/inet.h>
#    include <errno.h>
#    include <netdb.h>
#    include <sys/socket.h>
#    include <sys/types.h>
#    include <unistd.h>

namespace mpp
{
UDPSocket::UDPSocket() : m_socket(-1)
{
}

int UDPSocket::Send(SocketAddress address, const void* data, size_t size)
{
    int sent = sendto(m_socket, (const char*)data, size, 0, (sockaddr*)address.GetAddress(), sizeof(sockaddr_in));
    if (sent == SO_ERROR)
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
    if (received == SO_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to receive data from client.");
        return -1;
    }

    from.SetAddress(addr, sizeof(sockaddr_in));

    return received;
}

bool Listen(const String& ip, int port)
{
    m_socket = INVALID_SOCKET;

    if ((m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        MPP_LOG(LogLevel::Error, "Failed to create socket. " << errno);
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip.c_str());

    if (bind(m_socket, (sockaddr*)&address, sizeof(sockaddr_in)) == -1)
    {
        MPP_LOG(LogLevel::Error, "Failed to bind socket. " << errno);
        return false;
    }

    return true;
}

} // namespace mpp
#endif