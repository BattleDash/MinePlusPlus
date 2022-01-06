// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>
#include <Server/Network/Protocol/Packet.h>
#include <Server/Network/Protocol/Status/PacketStatusInListener.h>

namespace mpp
{
class ConnectionProtocol;
class PacketStatusInListener;

class PacketStatusInPing : public Packet<PacketStatusInListener>
{
  public:
    MPP_API PacketStatusInPing(int64_t time);
    MPP_API PacketStatusInPing(PacketDataSerializer* serializer);
    MPP_API ~PacketStatusInPing();

    MPP_API void Write(PacketDataSerializer* serializer) override;
    MPP_API void Handle(PacketStatusInListener* listener) override;

    int64_t m_time;
};

MPP_DECLARE_PACKET_TYPE(PacketStatusInPing)
} // namespace mpp