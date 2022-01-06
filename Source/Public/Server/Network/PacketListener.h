// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

namespace mpp
{
class NetworkManager;

class PacketListener
{
  public:
    MPP_API virtual void OnDisconnect(const String& reason) = 0;

    MPP_API virtual NetworkManager* GetConnection() = 0;
};
} // namespace mpp