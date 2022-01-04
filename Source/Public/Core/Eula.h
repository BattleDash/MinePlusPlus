// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

namespace mpp
{
class Eula
{
  public:
    MPP_API Eula(const String& filePath);

    bool m_accepted;
};
} // namespace mpp