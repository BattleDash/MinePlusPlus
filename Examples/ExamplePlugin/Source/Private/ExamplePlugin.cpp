// Copyright BattleDash. All Rights Reserved.

#include <ExamplePlugin.h>

#include <Base/Log.h>
#include <Core/MinePlusPlus.h>

namespace ExamplePlugin
{
ExamplePlugin::ExamplePlugin()
{
}

mpp::String ExamplePlugin::Name()
{
    return "ExamplePlugin";
}

void ExamplePlugin::OnEnable()
{
    MPP_LOG(mpp::LogLevel::Info, "Example plugin is pogging");
    //mpp::g_minePlusPlus->StartServer();
}

void ExamplePlugin::OnDisable()
{
}
} // namespace ExamplePlugin

MPP_PLUGIN_API mpp::Plugin* CreatePlugin()
{
    return new ExamplePlugin::ExamplePlugin();
}