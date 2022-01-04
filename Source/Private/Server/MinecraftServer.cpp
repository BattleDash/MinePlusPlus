// Copyright BattleDash. All Rights Reserved.

#include <Server/MinecraftServer.h>
#include <Plugins/PluginManager.h>

namespace mpp
{
MinecraftServer::MinecraftServer(const ServerProperties* properties)
: m_properties(properties), m_pluginManager(new PluginManager(properties))
{
}

MinecraftServer::~MinecraftServer()
{
}

void MinecraftServer::InitializeServer()
{
}

void MinecraftServer::EnablePlugins()
{
    for (const WrappedPlugin* plugin : m_pluginManager->m_plugins)
    {
        plugin->m_plugin->OnEnable();
    }
}
} // namespace mpp