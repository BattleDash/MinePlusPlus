// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Server/Network/PacketListener.h>
#include <Server/Network/Protocol/Packet.h>
#include <Server/Network/Protocol/Status/PacketStatusInStart.h>
#include <Server/Network/Protocol/Status/PacketStatusInPing.h>

namespace mpp
{
class PacketStatusInStart;
class PacketStatusInPing;

class PacketStatusInListener : public PacketListener
{
  public:
    MPP_API virtual void HandleStatusRequest(PacketStatusInStart* packet) = 0;
    MPP_API virtual void HandlePingRequest(PacketStatusInPing* packet) = 0;
};
} // namespace mpp