// Copyright BattleDash. All Rights Reserved.

#include <Base/Platform.h>
#include <Base/String.h>
#include <Core/ServerProperties.h>
#include <Util/PropertiesFormat.h>

#include <chrono>

namespace mpp
{
ServerProperties::ServerProperties(const String& filePath, const StartupSettings& startupSettings)
{
    Properties properties = Properties(filePath);
    onlineMode = startupSettings.onlineMode || properties.GetValue<bool>("online-mode", true);
    preventProxyConnections = properties.GetValue<bool>("prevent-proxy-connections", false);
    serverIp = startupSettings.host.empty() ? properties.GetValue<String>("server-ip", "0.0.0.0") : startupSettings.host;
    spawnAnimals = properties.GetValue<bool>("spawn-animals", true);
    spawnNpcs = properties.GetValue<bool>("spawn-npcs", true);
    pvp = properties.GetValue<bool>("pvp", true);
    allowFlight = properties.GetValue<bool>("allow-flight", false);
    resourcePack = properties.GetValue<String>("resource-pack", "");
    requireResourcePack = properties.GetValue<bool>("require-resource-pack", false);
    resourcePackPrompt = properties.GetValue<String>("resource-pack-prompt", "");
    motd = properties.GetValue<String>("motd", "A Minecraft Server");
    forceGamemode = properties.GetValue<bool>("force-gamemode", false);
    enforceWhitelist = properties.GetValue<bool>("enforce-whitelist", false);
    difficulty = EDifficulty::ByName(properties.GetValue<String>("difficulty", "Peaceful"));
    gamemode = EGamemode::ByName(properties.GetValue<String>("gamemode", "Survival"));
    levelName = startupSettings.worldDir.empty() ? properties.GetValue<String>("level-name", "world") : startupSettings.worldDir;
    serverPort = startupSettings.port == -1 ? properties.GetValue<int>("server-port", 25565) : startupSettings.port;
    announcePlayerAchievements = properties.GetValue<bool>("announce-player-achievements", false);
    enableQuery = properties.GetValue<bool>("enable-query", false);
    queryPort = properties.GetValue<int>("query-port", 25565);
    enableRcon = properties.GetValue<bool>("enable-rcon", false);
    rconPort = properties.GetValue<int>("rcon.port", 25575);
    rconPassword = properties.GetValue<String>("rcon.password", "");
    resourcePackHash = properties.GetValue<String>("resource-pack-hash", "");
    resourcePackSha1 = properties.GetValue<String>("resource-pack-sha1", "");
    hardcore = properties.GetValue<bool>("hardcore", false);
    allowNether = properties.GetValue<bool>("allow-nether", true);
    spawnMonsters = properties.GetValue<bool>("spawn-monsters", true);
    useNativeTransport = properties.GetValue<bool>("use-native-transport", false);
    enableCommandBlocks = properties.GetValue<bool>("enable-command-blocks", false);
    spawnProtection = properties.GetValue<int>("spawn-protection", 16);
    opPermissionLevel = properties.GetValue<int>("op-permission-level", 4);
    functionPermissionLevel = properties.GetValue<int>("function-permission-level", 2);
    maxTickTime = properties.GetValue<long>(
        "max-tick-time", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)).count());
    rateLimitPacketsPerSecond = properties.GetValue<int>("rate-limit", 10);
    viewDistance = properties.GetValue<int>("view-distance", 10);
    simulationDistance = properties.GetValue<int>("simulation-distance", 10);
    maxPlayers = startupSettings.maxPlayers == -1 ? properties.GetValue<int>("max-players", 20) : startupSettings.maxPlayers;
    networkCompressionThreshold = properties.GetValue<int>("network-compression-threshold", 256);
    broadcastRconToOps = properties.GetValue<bool>("broadcast-rcon-to-ops", true);
    broadcastConsoleToOps = properties.GetValue<bool>("broadcast-console-to-ops", true);
    maxWorldSize = properties.GetValue<int>("max-world-size", 29999984);
    syncChunkWrites = properties.GetValue<bool>("sync-chunk-writes", true);
    enableJmxMonitoring = properties.GetValue<bool>("enable-jmx-monitoring", false);
    enableStatus = properties.GetValue<bool>("enable-status", true);
    hideOnlinePlayers = properties.GetValue<bool>("hide-online-players", false);
    entityBroadcastRangePercentage = properties.GetValue<int>("entity-broadcast-range-percentage", 100);
    textFilteringConfig = properties.GetValue<String>("text-filtering-config", "");
    playerIdleTimeout = properties.GetValue<int>("player-idle-timeout", 0);
    whiteList = properties.GetValue<bool>("white-list", false);
    pluginsDirectory = startupSettings.pluginsDirectory.empty() ? properties.GetValue<String>("plugins-directory", "plugins") : startupSettings.pluginsDirectory;
    if (properties.GetComments().size() != 1)
    {
        properties.AddComment("MinePlusPlus server properties");
    }
    properties.Save();
}
} // namespace mpp