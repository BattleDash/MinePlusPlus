// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Core/ServerProperties.h>
#include <Plugins/WrappedPlugin.h>

#include <vector>

namespace mpp
{
class PluginManager
{
  public:
    MPP_API PluginManager(const ServerProperties* properties);
    MPP_API ~PluginManager();

    MPP_API void LoadPlugins();
    MPP_API void UnloadPlugins();
    MPP_API WrappedPlugin* LoadPlugin(const String& pluginPath);
    MPP_API void UnloadPlugin(const String& pluginPath);

    String m_pluginsDirectory;
    std::vector<WrappedPlugin*> m_plugins;
};
} // namespace mpp