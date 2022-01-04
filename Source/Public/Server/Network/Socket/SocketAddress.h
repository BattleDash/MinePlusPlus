// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

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
  private:
    unsigned char m_address[64];
    unsigned char m_length;
};
} // namespace mpp