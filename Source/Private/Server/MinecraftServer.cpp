// Copyright BattleDash. All Rights Reserved.

#include <Server/MinecraftServer.h>
#include <Plugins/PluginLoader.h>

namespace mpp
{
MinecraftServer::MinecraftServer(const ServerProperties* properties)
: m_properties(properties), m_pluginLoader(new PluginLoader(properties))
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
    for (const WrappedPlugin* plugin : m_pluginLoader->m_plugins)
    {
        plugin->m_plugin->OnEnable();
    }
}
} // namespace mpp