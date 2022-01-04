// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/PacketSplitter.h>

namespace mpp
{
PacketSplitter::PacketSplitter()
{
}

void PacketSplitter::ChannelRead(ChannelHandlerContext* context, void* object)
{
    ByteBuf* byteBuf = static_cast<ByteBuf*>(object);
    byteBuf->MarkReaderIndex();
    uint8_t packetList[3];

    for (int i = 0; i < sizeof(packetList); i++)
    {
        if (!byteBuf->IsReadable())
        {
            MPP_LOG(LogLevel::Debug, "Unreadable");
            byteBuf->ResetReaderIndex();
            return;
        }

        packetList[i] = byteBuf->ReadByte();
        if (packetList[i] >= 0)
        {
            MPP_LOG(LogLevel::Debug, "TODO: Create PacketDataSerializer");
        }
    }
}
} // namespace mpp