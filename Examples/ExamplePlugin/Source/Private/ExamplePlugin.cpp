// Copyright BattleDash. All Rights Reserved.

#include <ExamplePlugin.h>

#include <Base/Log.h>

namespace ExamplePlugin
{
mpp::String ExamplePlugin::Name()
{
    return "ExamplePlugin";
}

void ExamplePlugin::OnEnable()
{
    MPP_LOG(mpp::LogLevel::Info, "Example plugin.");
}

void ExamplePlugin::OnDisable()
{
}
} // namespace ExamplePlugin

MPP_PLUGIN_API mpp::Plugin* CreatePlugin()
{
    return new ExamplePlugin::ExamplePlugin();
}