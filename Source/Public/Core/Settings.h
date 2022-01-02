// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

namespace mpp
{
class Settings
{
  public:
    String minePlusPlusSettingsFile;
    String propertiesFile;
    String dateFormat;
    bool eulaAgree;
    bool convertLegacySigns;
    String fileEncoding = "UTF-8";
    String host;
    int port;
    String levelName;
    bool stripLogColors;
    int maxPlayers;
    bool noConsole;
    bool onlineMode;
    String pluginsDirectory;
    String worldDir;
};
} // namespace mpp