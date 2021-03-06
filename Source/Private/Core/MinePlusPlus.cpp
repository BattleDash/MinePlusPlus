// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Base/Version.h>
#include <Core/Eula.h>
#include <Core/MinePlusPlus.h>
#include <Core/ServerProperties.h>
#include <Server/DedicatedServer.h>

#include <thread>

namespace mpp
{
MinePlusPlus* g_minePlusPlus;

MinePlusPlus::MinePlusPlus(const StartupSettings& settings) : m_settings(settings)
{
    if (g_minePlusPlus != nullptr)
    {
        MPP_LOG(LogLevel::Fatal, "MinePlusPlus has already been initialized!");
        return;
    }
    g_minePlusPlus = this;
    MPP_LOG(LogLevel::Info, "MinePlusPlus for Minecraft " << MPP_MINECRAFT_VERSION << " (" << MPP_PROTOCOL_VERSION
                                                          << ")" << " starting...");
}

MinePlusPlus::~MinePlusPlus()
{
    MPP_LOG(LogLevel::Info, "MinePlusPlus shutting down...");
}

void MinePlusPlus::StartServer()
{
    if (m_settings.eulaAgree)
    {
        MPP_LOG(LogLevel::Warning, "You have used the MinePlusPlus command line EULA agreement flag.");
        MPP_LOG(LogLevel::Warning, "By using this setting you are indicating your agreement to Mojang's EULA "
                                   "(https://account.mojang.com/documents/minecraft_eula).");
        MPP_LOG(LogLevel::Warning,
                "If you do not agree to the above EULA please stop your server and remove this flag immediately.");
    }
    else
    {
        Eula eula("eula.txt");
        if (!eula.m_accepted)
        {
            MPP_LOG(LogLevel::Fatal,
                    "You must accept the EULA before using MinePlusPlus! See eula.txt for more information.");
            return;
        }
    }

    MPP_LOG(LogLevel::Info, "Loading properties");
    ServerProperties properties = ServerProperties(m_settings.propertiesFile, m_settings);
    std::thread serverThread(&DedicatedServer::InitializeServer, new DedicatedServer(&properties));
    serverThread.join();
}
} // namespace mpp