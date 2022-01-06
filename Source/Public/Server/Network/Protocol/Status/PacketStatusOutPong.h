// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>
#include <Server/Network/Protocol/Packet.h>

namespace mpp
{
class ConnectionProtocol;

class PacketStatusOutPong : public Packet<void>
{
  public:
    MPP_API PacketStatusOutPong(int64_t time);
    MPP_API PacketStatusOutPong(PacketDataSerializer* serializer);
    MPP_API ~PacketStatusOutPong();

    MPP_API void Write(PacketDataSerializer* serializer) override;
    MPP_API void Handle(void* listener) override;

    int64_t m_time;
};

MPP_DECLARE_PACKET_TYPE(PacketStatusOutPong)
} // namespace mpp