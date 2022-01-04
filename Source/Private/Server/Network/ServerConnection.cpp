// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/ServerConnection.h>
#include <Server/Network/LegacyPingHandler.h>
#include <Server/Network/PacketSplitter.h>
#include <Server/Network/PacketDecoder.h>

namespace mpp
{
ServerConnection::ServerConnection(MinecraftServer* server) : m_server(server), m_socketManager(new TCPSocketManager())
{
}

ServerConnection::~ServerConnection()
{
    delete m_socketManager;
}

void ServerConnection::StartTCPServer(String host, int port)
{
    MPP_LOG(LogLevel::Info, "Initializing connection...");

    m_socketManager = new TCPSocketManager();
    m_socketManager->ChildHandler([this](TCPSocketClient* client) {
        client->Pipeline()
            ->AddLast("legacy_query", new LegacyPingHandler(this))
            ->AddLast("packet_splitter", new PacketSplitter())
            ->AddLast("decoder", new PacketDecoder(EProtocolDirection::SERVERBOUND));
    });
    m_socketManager->Listen(host, port);
}
} // namespace mpp