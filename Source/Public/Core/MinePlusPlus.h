// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Core/Settings.h>

namespace mpp
{
class MinePlusPlus
{
  public:
    MPP_API MinePlusPlus(const Settings& settings);
    MPP_API ~MinePlusPlus();
    


  private:
    const Settings& m_settings;
};

extern MPP_API MinePlusPlus* g_minePlusPlus;
} // namespace mpp