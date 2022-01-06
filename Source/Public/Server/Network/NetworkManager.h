// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Buffer/ByteBuf.h>
#include <Server/Network/PacketListener.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/Protocol/EProtocolDirection.h>
#include <Server/Network/Protocol/Packet.h>
#include <Server/Network/Socket/TCP/Channel/ChannelInboundHandlerAdapter.h>
#include <Server/Network/Socket/TCP/TCPSocketClient.h>

namespace mpp
{
class NetworkManager : public ChannelInboundHandlerAdapter
{
  public:
    MPP_API NetworkManager(EProtocolDirection direction, TCPSocketClient* client);

    MPP_API void ChannelRead(ChannelHandlerContext* context, void* object) override;
    MPP_API void SetListener(PacketListener* packetListener);
    MPP_API void SetProtocol(ConnectionProtocol* connectionProtocol);
    MPP_API void Send(Packet<void>* packet);

  private:
    TCPSocketClient* m_client;
    EProtocolDirection m_receiving;
    PacketListener* m_packetListener;
};
} // namespace mpp