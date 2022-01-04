// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Server/Network/LegacyPingHandler.h>

namespace mpp
{
LegacyPingHandler::LegacyPingHandler(ServerConnection* serverConnection) : m_serverConnection(serverConnection)
{
}

LegacyPingHandler::~LegacyPingHandler()
{
}

void LegacyPingHandler::ChannelRead(void* object)
{
    MPP_LOG(LogLevel::Debug, "Reading from LegacyPingHandler");
}
} // namespace mpp