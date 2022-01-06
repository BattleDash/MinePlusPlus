// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/Protocol/Status/PacketStatusOutServerInfo.h>

namespace mpp
{
PacketStatusOutServerInfo::PacketStatusOutServerInfo()
{
}

PacketStatusOutServerInfo::PacketStatusOutServerInfo(PacketDataSerializer* serializer)
{
}

void PacketStatusOutServerInfo::Write(PacketDataSerializer* serializer)
{
    serializer->WriteUtf("{\"version\":{\"name\":\"MinePlusPlus\",\"protocol\":47},\"players\":{\"max\":100,\"online\":0,\"sample\":[]},\"description\":{\"text\":\"A Minecraft Server\"}}");
}

void PacketStatusOutServerInfo::Handle(void* listener)
{
}
} // namespace mpp