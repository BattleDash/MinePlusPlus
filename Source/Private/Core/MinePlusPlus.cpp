// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Base/Version.h>
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
    MPP_LOG(LogLevel::Info, "MinePlusPlus " << MPP_VERSION << " shutting down...");
}
} // namespace mpp