// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/Protocol/Status/PacketStatusOutPong.h>

namespace mpp
{
PacketStatusOutPong::PacketStatusOutPong(int64_t time) : m_time(time)
{
}

PacketStatusOutPong::PacketStatusOutPong(PacketDataSerializer* serializer)
{
}

void PacketStatusOutPong::Write(PacketDataSerializer* serializer)
{
    serializer->WriteLong(m_time);
}

void PacketStatusOutPong::Handle(void* listener)
{
}
} // namespace mpp