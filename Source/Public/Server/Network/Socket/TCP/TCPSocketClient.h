// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>

namespace mpp
{
    class TCPSocketClient
    {
    public:
        TCPSocketClient(int socket);
        ~TCPSocketClient();

        int Send(const void* data, size_t size);
        int Receive(void* data, size_t size);
        void Close();
    private:
        int m_socket;
    };
}