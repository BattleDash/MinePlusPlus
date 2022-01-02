// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Base/Version.h>
#include <Core/Eula.h>
#include <Core/MinePlusPlus.h>

namespace mpp
{
MinePlusPlus* g_minePlusPlus;

MinePlusPlus::MinePlusPlus(const Settings& settings) : m_settings(settings)
{
    g_minePlusPlus = this;
    MPP_LOG(LogLevel::Info, "MinePlusPlus " << MPP_VERSION << " for Minecraft " << MPP_MINECRAFT_VERSION << "("
                                            << MPP_PROTOCOL_VERSION << ")"
                                            << " starting on port " << m_settings.port << "...");
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
        MPP_LOG(LogLevel::Warning, "By using this setting you are indicating your agreement to Mojang's EULA (https://account.mojang.com/documents/minecraft_eula).");
        MPP_LOG(LogLevel::Warning, "If you do not agree to the above EULA please stop your server and remove this flag immediately.");
    }
    else
    {
        Eula eula("eula.txt");
        if (!eula.IsAccepted())
        {
            MPP_LOG(LogLevel::Fatal, "You must accept the EULA before using MinePlusPlus! See eula.txt for more information.");
            return;
        }
    }
}
} // namespace mpp