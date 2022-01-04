// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Rcon/RemoteStatusListener.h>

namespace mpp
{
struct sockaddr_in;

RemoteStatusListener::RemoteStatusListener(MinecraftServer* server, const String& host, int port)
    : m_server(server), m_socket(new UDPSocket())
{
    if (!m_socket->Listen(host, port))
    {
        MPP_LOG(LogLevel::Error, "Failed to start Query Listener");
        delete m_socket;
        m_socket = nullptr;
    }
    else
    {
        MPP_LOG(LogLevel::Debug, "Created Query Listener");
        m_thread = std::thread(&RemoteStatusListener::Run, this);
    }
}

void RemoteStatusListener::Run()
{
    while (true)
    {
        SocketAddress from;
        char buffer[1460];
        MPP_LOG(LogLevel::Info, "Waiting for packet...");
        int size = m_socket->Receive(buffer, sizeof(buffer), from);
        if (size > 0)
        {
            ProcessPacket(from, buffer, size);
        }
    }
}

void RemoteStatusListener::ProcessPacket(SocketAddress& from, void* data, size_t size)
{
    MPP_LOG(LogLevel::Debug, "Packet len " << size);
    auto buf = reinterpret_cast<unsigned char*>(data);
    // TODO: Implement from net.minecraft.server.rcon.thread.RemoteStatusListener
    if (3 <= size && -2 == buf[0] && -3 == buf[1])
    {

    }
}

} // namespace mpp