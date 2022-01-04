// Copyright BattleDash. All Rights Reserved.

#pragma once

#if defined(MPP_PLATFORM_LINUX)
#    include <Base/Log.h>
#    include <Server/Network/Socket/UDP/UDPSocket.h>

#    include <arpa/inet.h>
#    include <netdb.h>
#    include <sys/socket.h>
#    include <sys/types.h>
#    include <unistd.h>

namespace mpp
{
UDPSocket::UDPSocket() : m_socket(-1)
{
}

int UDPSocket::Send(SocketAddress& address, const void* data, size_t size)
{
    int sent = sendto(m_socket, (const char*)data, size, 0, (sockaddr*)address.GetAddress(), sizeof(sockaddr_in));
    if (sent == SOCKET_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to send data to client.");
        return -1;
    }

    return sent;
}

int UDPSocket::Receive(void* data, size_t size, sockaddr& from)
{
    socklen_t fromLength = sizeof(sockaddr_in);
	sockaddr_in addr;
    int received = recvfrom(m_socket, (char*)data, size, 0, (sockaddr*)&addr, &fromLength);
    if (received == SOCKET_ERROR)
    {
        MPP_LOG(LogLevel::Error, "Failed to receive data from client.");
        return -1;
    }

    from.SetAddress(addr, sizeof(sockaddr_in));

    return received;
}

bool Listen(const String& ip, int port)
{
    return true;
}

} // namespace mpp
#endif