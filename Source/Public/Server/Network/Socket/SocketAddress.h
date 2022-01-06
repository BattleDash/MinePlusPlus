// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

#if defined(MPP_PLATFORM_WINDOWS)
#    include <WinSock2.h>
#    include <ws2tcpip.h>
#elif defined(MPP_PLATFORM_LINUX)
#    include <string.h>
#    include <sys/socket.h>
#    include <netinet/in.h>
#    include <netinet/ip.h>
#    include <arpa/inet.h>
#endif

namespace mpp
{
class SocketAddress
{
  public:
    SocketAddress()
    {
        m_length = 0;
        memset(m_address, 0, sizeof(m_address));
    }

    SocketAddress(const void* data, int len)
    {
        SetAddress(data, len);
    }

    void SetAddress(const void* data, int len)
    {
        m_length = len;
        memcpy(m_address, data, m_length);
    }

    const unsigned char* GetAddress() const
    {
        return m_address;
    }

    int GetLength() const
    {
        return m_length;
    }

    String GetIPString()
    {
        struct sockaddr* sa = reinterpret_cast<sockaddr*>(m_address);
        if (sa->sa_family == AF_INET)
        {
            struct sockaddr_in* sin = reinterpret_cast<sockaddr_in*>(sa);
            return String(inet_ntoa(sin->sin_addr));
        }
        else if (sa->sa_family == AF_INET6)
        {
            struct sockaddr_in6* sin6 = reinterpret_cast<sockaddr_in6*>(sa);
            return "";
            //return String(inet_ntop(AF_INET6, &sin6->sin6_addr, m_ipString, sizeof(m_ipString)));
        }
        else
        {
            return "Unknown Protocol";
        }
    }

    int GetPort()
    {
        struct sockaddr* sa = reinterpret_cast<sockaddr*>(m_address);
        if (sa->sa_family == AF_INET)
        {
            struct sockaddr_in* sin = reinterpret_cast<sockaddr_in*>(sa);
            return ntohs(sin->sin_port);
        }
        else if (sa->sa_family == AF_INET6)
        {
            struct sockaddr_in6* sin6 = reinterpret_cast<sockaddr_in6*>(sa);
            return ntohs(sin6->sin6_port);
        }
        else
        {
            return -1;
        }
    }

  private:
    unsigned char m_address[64];
    unsigned char m_length;
};
} // namespace mpp