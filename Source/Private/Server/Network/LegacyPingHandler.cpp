// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Base/String.h>
#include <Server/Network/LegacyPingHandler.h>

#include <wchar.h>

namespace mpp
{
LegacyPingHandler::LegacyPingHandler(ServerConnection* serverConnection) : m_serverConnection(serverConnection)
{
}

bool LegacyPingHandler::AttemptHandlePingPacket(ChannelHandlerContext* context, ByteBuf* byteBuf)
{
    if (byteBuf->ReadUnsignedByte() != 254)
    {
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
        bool queryPacket = byteBuf->ReadUnsignedByte() == 1;

        queryPacket &= byteBuf->ReadUnsignedByte() == 250;
        queryPacket &= wcscmp(L"MC|PingHost", byteBuf->ReadWString(byteBuf->ReadShort())) == 0;
        int j = byteBuf->ReadUnsignedShort();

        queryPacket &= byteBuf->ReadUnsignedByte() >= 73;
        queryPacket &= 3 + (wcslen(byteBuf->ReadWString(byteBuf->ReadShort())) * 2) + 4 == j;
        queryPacket &= byteBuf->ReadInt() <= 65535;
        queryPacket &= byteBuf->ReadableBytes() == 0;
        if (!queryPacket)
        {
            return false;
        }

        SocketAddress& addr = context->m_pipeline->m_client->m_address;
        MPP_LOG(LogLevel::Debug, "Ping: (1.6) from " << addr.GetIPString() << ":" << addr.GetPort());
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
        context->m_pipeline->Remove("legacy_query");
        context->FireChannelRead(object);
    }
}
} // namespace mpp