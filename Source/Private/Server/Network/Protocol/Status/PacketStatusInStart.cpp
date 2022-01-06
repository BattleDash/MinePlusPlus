// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Protocol/ConnectionProtocol.h>
#include <Server/Network/Protocol/Status/PacketStatusInStart.h>

namespace mpp
{
PacketStatusInStart::PacketStatusInStart(PacketDataSerializer* serializer)
{
}

void PacketStatusInStart::Write(PacketDataSerializer* serializer)
{
}

void PacketStatusInStart::Handle(PacketStatusInListener* listener)
{
    listener->HandleStatusRequest(this);
}
} // namespace mpp