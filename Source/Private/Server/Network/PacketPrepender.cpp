// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/Buffer/PacketDataSerializer.h>
#include <Server/Network/Buffer/Unpooled.h>
#include <Server/Network/PacketPrepender.h>

namespace mpp
{
void PacketPrepender::Write(ChannelHandlerContext* context, void* object)
{
    ByteBuf* buffer = static_cast<ByteBuf*>(object);
    int readableBytes = buffer->ReadableBytes();
    int size = PacketDataSerializer::GetVarIntSize(readableBytes);
    if (size > 3)
    {
        throw new std::runtime_error(String(String("Unable to fit ") + std::to_string(size) + String(" into 3 bytes")).c_str());
    }
    ByteBuf* newBuf = Unpooled::Buffer();
    PacketDataSerializer serializer(newBuf);
    serializer.WriteVarInt(readableBytes);
    serializer.WriteBytes(buffer->GetData(), buffer->ReaderIndex(), readableBytes);
    context->Write(newBuf);
}
} // namespace mpp