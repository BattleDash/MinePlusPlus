// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Plugins/PluginLoader.h>

#include <filesystem>

#if MPP_PLATFORM_WINDOWS
#    include <Windows.h>
#endif

namespace mpp
{
PluginLoader::PluginLoader(const ServerProperties* properties) : m_pluginsDirectory(properties->pluginsDirectory)
{
}

PluginLoader::~PluginLoader()
{
}

WrappedPlugin* PluginLoader::LoadPlugin(const std::string& pluginPath)
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

void PluginLoader::LoadPlugins()
{
    for (const auto& pluginPath : std::filesystem::directory_iterator(m_pluginsDirectory))
    {
        MPP_LOG(LogLevel::Info, "Loading plugin '" << pluginPath.path().string() << "'");
        WrappedPlugin* plugin = LoadPlugin(pluginPath.path().string());
        m_plugins.push_back(plugin);
    }
}
} // namespace mpp