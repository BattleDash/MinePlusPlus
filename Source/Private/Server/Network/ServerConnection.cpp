// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/HandshakeListener.h>
#include <Server/Network/LegacyPingHandler.h>
#include <Server/Network/NetworkManager.h>
#include <Server/Network/PacketDecoder.h>
#include <Server/Network/PacketEncoder.h>
#include <Server/Network/PacketPrepender.h>
#include <Server/Network/PacketSplitter.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/ServerConnection.h>

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
            ->AddLast("decoder", new PacketDecoder(EProtocolDirection::SERVERBOUND))
            ->AddLast("prepender", new PacketPrepender())
            ->AddLast("encoder", new PacketEncoder(EProtocolDirection::CLIENTBOUND));

        NetworkManager* networkManager = new NetworkManager(EProtocolDirection::SERVERBOUND, client);
        client->Pipeline()->AddLast("packet_handler", networkManager);
        networkManager->SetListener(new HandshakeListener(m_server, networkManager));
    });
    m_socketManager->Listen(host, port);

    ConnectionProtocol::Initialize();
}
} // namespace mpp