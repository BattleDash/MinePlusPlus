// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <Core/ServerProperties.h>
#include <Server/MinecraftServer.h>

namespace mpp
{
class DedicatedServer : MinecraftServer
{
  public:
    MPP_API DedicatedServer(const ServerProperties* properties);
    MPP_API ~DedicatedServer();

    MPP_API void InitializeServer();
};
} // namespace mpp