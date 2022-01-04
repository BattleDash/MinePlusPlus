// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Base/Version.h>
#include <Core/ServerProperties.h>
#include <Server/DedicatedServer.h>

#include <chrono>
#include <thread>

namespace mpp
{
DedicatedServer::DedicatedServer(const ServerProperties* properties)
: MinecraftServer(properties)
{
}

DedicatedServer::~DedicatedServer()
{
}

void DedicatedServer::InitializeServer()
{
    // TODO: Server console handler thread

    MPP_LOG(LogLevel::Info, "MinePlusPlus server starting on port " << m_properties->serverPort << "...");
    MPP_LOG(LogLevel::Info, "Default game type: " << m_properties->gamemode->m_name);
    MPP_LOG(LogLevel::Info,
            "This server is running MinePlusPlus version " << MPP_VERSION << " (MC: " << MPP_MINECRAFT_VERSION << ")");

    m_pluginManager->LoadPlugins();
    EnablePlugins();

    MPP_LOG(LogLevel::Info, "Loaded and enabled plugins");

    m_serverConnection = new ServerConnection(this);
    m_serverConnection->StartTCPServer(m_properties->serverIp, m_properties->serverPort);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
} // namespace mpp