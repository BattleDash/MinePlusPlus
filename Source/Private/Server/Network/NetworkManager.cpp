// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/NetworkManager.h>

namespace mpp
{
NetworkManager::NetworkManager(EProtocolDirection direction, TCPSocketClient* client)
    : m_receiving(direction), m_client(client), m_packetListener(nullptr)
{
    SetProtocol(ConnectionProtocol::GetProtocol(-1));
}

void NetworkManager::ChannelRead(ChannelHandlerContext* context, void* object)
{
    Packet<void>* packet = static_cast<Packet<void>*>(object);
    if (packet != nullptr)
    {
        if (m_packetListener != nullptr)
        {
            packet->Handle(m_packetListener);
        }
    }
}

void NetworkManager::SetListener(PacketListener* packetListener)
{
    m_packetListener = packetListener;
}

void NetworkManager::SetProtocol(ConnectionProtocol* connectionProtocol)
{
    m_client->Attr("protocol", connectionProtocol);
}

void NetworkManager::Send(Packet<void>* packet)
{
    try
    {
        m_client->Pipeline()->m_tail->Write(packet);
    }
    catch (const std::exception& e)
    {
        MPP_LOG(LogLevel::Error, "Failed to send packet: " << e.what());
    }
    catch (...)
    {
        MPP_LOG(LogLevel::Error, "Failed to send packet " << packet->Name());
    }
}
} // namespace mpp