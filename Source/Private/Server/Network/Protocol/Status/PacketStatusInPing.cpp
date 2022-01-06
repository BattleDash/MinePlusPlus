// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/Protocol/Status/PacketStatusInPing.h>

namespace mpp
{
PacketStatusInPing::PacketStatusInPing(int64_t time) : m_time(time)
{
}

PacketStatusInPing::PacketStatusInPing(PacketDataSerializer* serializer)
{
    m_time = serializer->ReadLong();
}

void PacketStatusInPing::Write(PacketDataSerializer* serializer)
{
    serializer->WriteLong(m_time);
}

void PacketStatusInPing::Handle(PacketStatusInListener* listener)
{
    listener->HandlePingRequest(this);
}
} // namespace mpp