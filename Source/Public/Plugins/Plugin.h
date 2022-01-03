// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

namespace mpp
{
class Plugin
{
  public:
    virtual String Name() = 0;
    virtual void OnEnable() = 0;
    virtual void OnDisable() = 0;
};
} // namespace mpp