// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>
#include <World/EDifficulty.h>
#include <World/Level/EGamemode.h>
#include <Core/StartupSettings.h>

namespace mpp
{
class ServerProperties
{
  public:
    MPP_API ServerProperties(const String& filePath, const StartupSettings& startupSettings);

    bool onlineMode;
    bool preventProxyConnections;
    String serverIp;
    bool spawnAnimals;
    bool spawnNpcs;
    bool pvp;
    bool allowFlight;
    String resourcePack;
    bool requireResourcePack;
    String resourcePackPrompt;
    String motd;
    bool forceGamemode;
    bool enforceWhitelist;
    EDifficulty* difficulty;
    EGamemode* gamemode;
    String levelName;
    int serverPort;
    bool announcePlayerAchievements;
    bool enableQuery;
    int queryPort;
    bool enableRcon;
    int rconPort;
    String rconPassword;
    String resourcePackHash;
    String resourcePackSha1;
    bool hardcore;
    bool allowNether;
    bool spawnMonsters;
    bool useNativeTransport;
    bool enableCommandBlocks;
    int spawnProtection;
    int opPermissionLevel;
    int functionPermissionLevel;
    long maxTickTime;
    int rateLimitPacketsPerSecond;
    int viewDistance;
    int simulationDistance;
    int maxPlayers;
    int networkCompressionThreshold;
    bool broadcastRconToOps;
    bool broadcastConsoleToOps;
    int maxWorldSize;
    bool syncChunkWrites;
    bool enableJmxMonitoring;
    bool enableStatus;
    bool hideOnlinePlayers;
    int entityBroadcastRangePercentage;
    String textFilteringConfig;
    int playerIdleTimeout;
    bool whiteList;
    String pluginsDirectory;
};
} // namespace mpp