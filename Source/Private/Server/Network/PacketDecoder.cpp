// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/PacketDecoder.h>

namespace mpp
{
PacketDecoder::PacketDecoder(EProtocolDirection direction) : m_direction(direction)
{
}

void PacketDecoder::ChannelRead(ChannelHandlerContext* context, void* object)
{
    ByteBuf* buffer = static_cast<ByteBuf*>(object);
    context->Close();
}
} // namespace mpp