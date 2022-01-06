// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Server/Network/PacketListener.h>
#include <Server/Network/Protocol/Packet.h>

namespace mpp
{
class PacketHandshakingInSetProtocol;

class PacketHandshakingInListener : public PacketListener
{
  public:
    MPP_API virtual void HandleIntention(PacketHandshakingInSetProtocol* packet) = 0;
};
} // namespace mpp