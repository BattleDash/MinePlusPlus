// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Socket/TCP/TCPSocketManager.h>

namespace mpp
{
TCPSocketManager::TCPSocketManager() : m_socket(new TCPSocketServer()), m_listening(false)
{
}

TCPSocketManager::~TCPSocketManager()
{
    delete m_socket;
    MPP_LOG(LogLevel::Debug, "Deconstructed TCPSocketManager");
}

bool TCPSocketManager::Listen(const String& ip, int port)
{
    MPP_LOG(LogLevel::Info, "Starting TCP Server...");

    if (!m_socket->Listen(ip, port))
    {
        MPP_LOG(LogLevel::Error, "Failed to start TCP Server");
        return false;
    }
    m_listening = true;
    m_acceptThread = std::thread(&TCPSocketManager::AcceptClients, this);
    m_thread = std::thread(&TCPSocketManager::Run, this);
    return true;
}

std::vector<TCPSocketClient*>& TCPSocketManager::Clients()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_clients;
}

void TCPSocketManager::ChildHandler(std::function<void(TCPSocketClient*)> childHandler)
{
    m_childHandler = childHandler;
}

void TCPSocketManager::AcceptClients()
{
    while (m_listening)
    {
        TCPSocketClient* client = m_socket->Accept();
        if (client)
        {
            MPP_LOG(LogLevel::Debug, "Accepted client");
            m_childHandler(client);
            Clients().push_back(client);
        }
    }
}

void TCPSocketManager::Run()
{
    while (m_listening)
    {
        //MPP_LOG(LogLevel::Debug, "Iterating clients...");
        for (TCPSocketClient* client : Clients())
        {
            if (client->m_connected)
            {
                char buffer[2048];
                MPP_LOG(LogLevel::Debug, "Waiting for message...");
                int size = client->Receive(buffer, sizeof(buffer));
                if (size > 0)
                {
                    MPP_LOG(LogLevel::Debug, "Received " << size << " bytes");
                    // Iterate handlers of pipeline
                    for (std::pair<String, ChannelInboundHandler*> pair : client->Pipeline()->Handlers())
                    {
                        pair.second->ChannelRead(buffer);
                    }
                }
                else
                {
                    MPP_LOG(LogLevel::Debug, "Disconnected");
                    client->Close();
                    Clients().erase(std::remove(Clients().begin(), Clients().end(), client), Clients().end());
                }
            }
            else
            {
                client->Close();
                Clients().erase(std::remove(Clients().begin(), Clients().end(), client), Clients().end());
                MPP_LOG(LogLevel::Debug, "Removed client");
            }
        }
    }
}
} // namespace mpp