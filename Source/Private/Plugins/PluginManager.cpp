// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Plugins/PluginManager.h>

#include <filesystem>

#if defined(MPP_PLATFORM_WINDOWS)
#    include <Windows.h>
#elif defined(MPP_PLATFORM_LINUX)
#    include <dlfcn.h>
#endif

namespace mpp
{
PluginManager::PluginManager(const ServerProperties* properties) : m_pluginsDirectory(properties->pluginsDirectory)
{
}

PluginManager::~PluginManager()
{
    for (WrappedPlugin* plugin : m_plugins)
    {
        plugin->m_plugin->OnDisable();
        delete plugin;
    }
}

WrappedPlugin* PluginManager::LoadPlugin(const std::string& pluginPath)
{
    // Relative to the base dir
    std::filesystem::path pluginFilePath = std::filesystem::absolute(pluginPath);

    if (std::filesystem::exists(pluginFilePath))
    {
        Plugin* (*pluginFunction)();

        // Check if the file extension is dll or so
        if (pluginFilePath.extension() == ".so")
        {
#if MPP_PLATFORM_LINUX
            // Load the plugin
            void* pluginLibrary = dlopen(pluginFilePath.string().c_str(), RTLD_LAZY);

            if (pluginLibrary != nullptr)
            {
                pluginFunction = reinterpret_cast<Plugin* (*)()>(dlsym(pluginLibrary, "CreatePlugin"));

                if (pluginFunction == nullptr)
                {
                    dlclose(pluginLibrary);
                    MPP_LOG(LogLevel::Error, "Could not load '" << pluginLibraryFullPath.string()
                                                                << "'. Could not find CreatePlugin function.");
                    return NULL;
                }
            }
#endif
        }
        else if (pluginFilePath.extension() == ".dll")
        {
#if MPP_PLATFORM_WINDOWS
            // Load the plugin
            HMODULE pluginLibrary = LoadLibrary(pluginFilePath.string().c_str());

            if (pluginLibrary != nullptr)
            {
                pluginFunction = reinterpret_cast<Plugin* (*)()>(GetProcAddress(pluginLibrary, "?CreatePlugin@@YAPEAVPlugin@mpp@@XZ"));

                if (pluginFunction == nullptr)
                {
                    FreeLibrary(pluginLibrary);
                    MPP_LOG(LogLevel::Error, "Could not load '" << pluginFilePath.string()
                                                                << "'. Could not find CreatePlugin function");
                    return nullptr;
                }
            }
#endif
        }
        else
        {
            MPP_LOG(LogLevel::Error,
                    "Could not load '" << pluginFilePath.string() << "'. Unknown file extension");
            return nullptr;
        }

        // Get the plugin
        Plugin* plugin = pluginFunction();
        if (plugin == nullptr)
        {
            MPP_LOG(LogLevel::Error, "Could not load '" << pluginFilePath.string() << "'. Plugin is null");
            return nullptr;
        }
        return new WrappedPlugin(plugin);
    }
    else
    {
        MPP_LOG(LogLevel::Error, "Could not load '" << pluginFilePath.string() << "'. File does not exist");
        return nullptr;
    }
}

void PluginManager::LoadPlugins()
{
    for (const auto& pluginPath : std::filesystem::directory_iterator(m_pluginsDirectory))
    {
        WrappedPlugin* plugin = LoadPlugin(pluginPath.path().string());
        MPP_LOG(LogLevel::Info, "Loaded " << plugin->m_plugin->Name());
        m_plugins.push_back(plugin);
    }
}
} // namespace mpp