// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>
#include <Server/Network/PacketListener.h>
#include <Server/Network/Protocol/EProtocolDirection.h>

namespace mpp
{
template <typename T> class Packet
{
  public:
    MPP_API virtual void Write(PacketDataSerializer* serializer) = 0;
    MPP_API virtual void Handle(T* listener) = 0;

    MPP_API void IsSkippable()
    {
        return false;
    }
};

typedef void* (*CreatePacketFunc_t)(PacketDataSerializer*);

struct PacketWrapper
{
    CreatePacketFunc_t ctor;
    String name;
};

struct PacketFlow
{
    EProtocolDirection direction;
    PacketWrapper* packets;
    int count;
};

#define MPP_DECLARE_PACKET_TYPE(name)                                                                                  \
    static void* Create##name(PacketDataSerializer* serializer)                                                        \
    {                                                                                                                  \
        return new name(serializer);                                                                                   \
    }

#define MPP_BEGIN_PACKET_TABLE(name) static mpp::PacketWrapper s_packet_wrappers_##name[] = {

#define MPP_PACKET(name) {Create##name, #name},

#define MPP_END_PACKET_TABLE()                                                                                         \
    }                                                                                                                  \
    ;

#define MPP_BEGIN_PROTOCOL(protocolId) static mpp::PacketFlow s_packet_flow_##protocolId[] = {

#define MPP_PROTOCOL_FLOW(direction, packetTable)                                                                      \
    {direction, s_packet_wrappers_##packetTable, sizeof(s_packet_wrappers_##packetTable) / sizeof(mpp::PacketWrapper)},

#define MPP_END_PROTOCOL()                                                                                             \
    }                                                                                                                  \
    ;

} // namespace mpp