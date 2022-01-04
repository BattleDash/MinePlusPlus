// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>

namespace mpp
{
    class TCPSocket
    {
    public:
        TCPSocket();
        ~TCPSocket();

        bool Send(const String& data);
        bool Receive(String& data);
        void Close();

        bool IsConnected() const;
        bool IsListening() const;

    private:
        bool m_connected;
        bool m_listening;
        int m_socket;
    };
}