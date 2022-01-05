// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/LegacyPingHandler.h>
#include <Server/Network/Buffer/Unpooled.h>

#include <wchar.h>
#include <sstream>

namespace mpp
{
LegacyPingHandler::LegacyPingHandler(ServerConnection* serverConnection) : m_serverConnection(serverConnection)
{
}

ByteBuf* LegacyPingHandler::CreateReply(const WideString& data)
{
    ByteBuf* byteBuf = Unpooled::Buffer();
    byteBuf->WriteByte(255);
    byteBuf->WriteShort(data.length());
    const wchar_t* str = data.c_str();
    for (size_t i = 0; i < data.length(); i++)
    {
        byteBuf->WriteShort(str[i]);
    }
    return byteBuf;
}

void LegacyPingHandler::SendAndClose(ChannelHandlerContext* context, ByteBuf* byteBuf)
{
    context->Write(byteBuf);
    context->Close();
}

bool LegacyPingHandler::AttemptHandlePingPacket(ChannelHandlerContext* context, ByteBuf* byteBuf)
{
    if (byteBuf->ReadUnsignedByte() != 254)
    {
        return false;
    }

    int readableBytes = byteBuf->ReadableBytes();
    SocketAddress& addr = context->m_pipeline->m_client->m_address;

    switch (readableBytes)
    {
    case 0:
        MPP_LOG(LogLevel::Debug, "Ping: (<1.3.x) from " << addr.GetIPString() << ":" << addr.GetPort());
        break;
    case 1:
        MPP_LOG(LogLevel::Debug, "Ping: (1.4-1.5.x) from " << addr.GetIPString() << ":" << addr.GetPort());
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
            MPP_LOG(LogLevel::Debug, "Ping: (invalid 1.6) from " << addr.GetIPString() << ":" << addr.GetPort());
            return false;
        }

        MPP_LOG(LogLevel::Debug, "Ping: (1.6) from " << addr.GetIPString() << ":" << addr.GetPort());
        WideString serverVersion = L"MinePlusPlus 1.18.1";
        WideString motd = L"Test";
        int players = 1;
        int maxPlayers = 1;
        std::wstringstream ss;
        ss << L"\u00a71\u0000" << 127 << "\u0000" << serverVersion << "\u0000" << motd << "\u0000" << players << "\u0000" << maxPlayers;
        //std::wcout << ss.str() << std::endl;
        SendAndClose(context, CreateReply(WideString(ss.str())));
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