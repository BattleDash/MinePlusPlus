// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Core/ServerProperties.h>
#include <Plugins/PluginLoader.h>

namespace mpp
{
class MinecraftServer
{
  public:
    MPP_API MinecraftServer(const ServerProperties* properties);
    MPP_API ~MinecraftServer();

    MPP_API void InitializeServer();
    MPP_API void EnablePlugins();

    const ServerProperties* m_properties;
    PluginLoader* m_pluginLoader;
};
} // namespace mpp