// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Plugins/Plugin.h>

namespace ExamplePlugin
{
class ExamplePlugin : public mpp::Plugin
{
  public:
    mpp::String Name() override;
    void OnEnable() override;
    void OnDisable() override;
};
} // namespace ExamplePlugin