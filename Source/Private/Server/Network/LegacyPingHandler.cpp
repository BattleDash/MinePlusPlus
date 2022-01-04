// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/LegacyPingHandler.h>

namespace mpp
{
LegacyPingHandler::LegacyPingHandler(ServerConnection* serverConnection) : m_serverConnection(serverConnection)
{
}

bool LegacyPingHandler::AttemptHandlePingPacket(ChannelHandlerContext* context, ByteBuf* byteBuf)
{
    if (byteBuf->ReadUnsignedByte() != 254)
    {
        MPP_LOG(LogLevel::Debug, "First unsigned byte was not 254");
        return false;
    }

    int readableBytes = byteBuf->ReadableBytes();

    switch (readableBytes)
    {
        case 0:
            MPP_LOG(LogLevel::Debug, "Using Legacy Ping Format 0");
            break;
        case 1:
            MPP_LOG(LogLevel::Debug, "Using Legacy Ping Format 1");
            break;
        default:
            MPP_LOG(LogLevel::Debug, "Using Legacy Ping Format 2 " << readableBytes);
            break;
    }

    return true;
}

void LegacyPingHandler::ChannelRead(ChannelHandlerContext* context, void* object)
{
    ByteBuf* byteBuf = static_cast<ByteBuf*>(object);
    byteBuf->MarkReaderIndex();

    if (!AttemptHandlePingPacket(context, byteBuf))
    {
        byteBuf->ResetReaderIndex();
        //context->m_socket->Pipeline()->Remove("legacy_query");
        //context->FireChannelRead(object);
    }

    MPP_LOG(LogLevel::Debug, "Read from LegacyPingHandler");
}
} // namespace mpp