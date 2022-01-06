// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>
#include <Server/Network/Protocol/Packet.h>
#include <Server/Network/Protocol/Status/PacketStatusInListener.h>

namespace mpp
{
class ConnectionProtocol;
class PacketStatusInListener;

class PacketStatusInStart : public Packet<PacketStatusInListener>
{
  public:
    MPP_API PacketStatusInStart();
    MPP_API PacketStatusInStart(PacketDataSerializer* serializer);
    MPP_API ~PacketStatusInStart();

    MPP_API void Write(PacketDataSerializer* serializer) override;
    MPP_API void Handle(PacketStatusInListener* listener) override;
};

MPP_DECLARE_PACKET_TYPE(PacketStatusInStart)
} // namespace mpp