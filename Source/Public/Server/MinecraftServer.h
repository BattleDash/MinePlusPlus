// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Core/ServerProperties.h>
#include <Plugins/PluginManager.h>
#include <Server/Network/ServerConnection.h>

namespace mpp
{
class ServerConnection;

class MinecraftServer
{
  public:
    MPP_API MinecraftServer(const ServerProperties* properties);
    MPP_API ~MinecraftServer();

    MPP_API void InitializeServer();
    MPP_API void EnablePlugins();

    const ServerProperties* m_properties;
    PluginManager* m_pluginManager;
    ServerConnection* m_serverConnection;
};
} // namespace mpp