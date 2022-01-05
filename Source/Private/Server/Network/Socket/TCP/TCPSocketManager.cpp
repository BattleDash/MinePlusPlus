// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Buffer/Unpooled.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundHandler.h>
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
    m_thread = std::thread(&TCPSocketManager::Run, this);
    return true;
}

std::vector<TCPSocketClient*>& TCPSocketManager::Clients()
{
    return m_clients;
}

void TCPSocketManager::ChildHandler(std::function<void(TCPSocketClient*)> childHandler)
{
    m_childHandler = childHandler;
}

void TCPSocketManager::Run()
{
    while (m_listening)
    {
        std::vector<TCPSocketClient*>& clients = Clients();
        TCPSocketClient* acceptedClient = m_socket->Accept();
        if (acceptedClient)
        {
            MPP_LOG(LogLevel::Debug, "Accepted client");
            m_childHandler(acceptedClient);
            clients.push_back(acceptedClient);
        }

        for (auto it = clients.begin(); it != clients.end();)
        {
            TCPSocketClient* client = *it;
            if (client->m_connected)
            {
                char buffer[2048];
                int size = client->Receive(buffer, sizeof(buffer));
                if (size > 0)
                {
                    try
                    {
                        ByteBuf* buf = Unpooled::WrapArray(buffer, size);
                        MPP_LOG(LogLevel::Debug, "Received " << size << " bytes");
                        MPP_LOG(LogLevel::Debug, "Pipeline is " << client->Pipeline()->ToString());
                        client->Pipeline()->m_head->FireChannelRead(buf);
                        MPP_LOG(LogLevel::Debug, "Pipeline complete");
                        delete buf;
                    }
                    catch (const std::exception& e)
                    {
                        MPP_LOG(LogLevel::Error, "Exception: " << e.what());
                    }
                }
                else if (size == -1)
                {
                    client->m_connected = false;
                }
            }
            if (!client->m_connected)
            {
                MPP_LOG(LogLevel::Debug, "Client disconnected");
                it = clients.erase(it);
                client->Close();
                // delete client;
            }
            else
            {
                ++it;
            }
        }
    }
}
} // namespace mpp