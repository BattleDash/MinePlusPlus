// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>
#include <Server/Network/Protocol/Packet.h>

namespace mpp
{
class ConnectionProtocol;

struct ServerPing
{
    int64_t m_time;
};

class PacketStatusOutServerInfo : public Packet<void>
{
  public:
    MPP_API PacketStatusOutServerInfo();
    MPP_API PacketStatusOutServerInfo(PacketDataSerializer* serializer);
    MPP_API ~PacketStatusOutServerInfo();

    MPP_API void Write(PacketDataSerializer* serializer) override;
    MPP_API void Handle(void* listener) override;
};

MPP_DECLARE_PACKET_TYPE(PacketStatusOutServerInfo)
} // namespace mpp