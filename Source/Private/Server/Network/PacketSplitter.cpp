// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>
#include <Server/Network/Buffer/Unpooled.h>
#include <Server/Network/PacketSplitter.h>

namespace mpp
{
void PacketSplitter::ChannelRead(ChannelHandlerContext* context, void* object)
{
    ByteBuf* byteBuf = static_cast<ByteBuf*>(object);
    byteBuf->MarkReaderIndex();
    uint8_t packetList[3];

    while (true)
    {
        for (int i = 0; i < 3; i++)
        {
            if (!byteBuf->IsReadable())
            {
                byteBuf->ResetReaderIndex();
                return;
            }

            packetList[i] = byteBuf->ReadByte();
            if (packetList[i] >= 0)
            {
                PacketDataSerializer packetDataSerializer(Unpooled::WrapArray(packetList, sizeof(packetList)));
                int size = packetDataSerializer.ReadVarInt();
                if (byteBuf->ReadableBytes() >= size)
                {
                    ByteBuf* packet = byteBuf->ReadBytes(size);
                    context->FireChannelRead(static_cast<void*>(packet));
                }
                else
                {
                    MPP_LOG(LogLevel::Debug, "Not enough bytes");
                    byteBuf->ResetReaderIndex();
                }
                break;
            }
        }
    }
}
} // namespace mpp