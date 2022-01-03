// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Base/Platform.h>
#include <Base/String.h>
#include <Base/Version.h>
#include <Core/Main.h>
#include <Core/MinePlusPlus.h>
#include <Core/Settings.h>

#include <tclap/CmdLine.h>

#if defined(MPP_PLATFORM_WINDOWS)
#    include <Windows.h>
#endif

int main(int argc, char** argv)
{
    return mpp::RealMain(argc, argv);
}

namespace mpp
{
Settings ParseSettings(int argc, char** argv)
{
    TCLAP::CmdLine cmd("MinePlusPlus", ' ',
                       String(MPP_PLATFORM_NAME) + "-" + String(MPP_BUILD_CHANNEL_NAME) + "-" + String(MPP_VERSION));
    TCLAP::ValueArg<String> minePlusPlusSettingsFileArg("", "config", "MinePlusPlus configuration file", false, "",
                                                        "string", cmd);
    TCLAP::ValueArg<String> propertiesFileArg("", "properties", "MinePlusPlus properties file", false, "server.properties", "string", cmd);
    TCLAP::ValueArg<String> dateFormatArg("", "date-format", "Date format", false, "", "string", cmd);
    TCLAP::SwitchArg eulaAgreeArg("", "eula-agree", "Agree to the Minecraft EULA", cmd, false);
    TCLAP::ValueArg<String> fileEncodingArg("", "file-encoding", "File encoding", false, "UTF-8", "string", cmd);
    TCLAP::ValueArg<String> hostArg("", "host", "Server host", false, "localhost", "string", cmd);
    TCLAP::ValueArg<int> portArg("", "port", "Server port", false, 25565, "port", cmd);
    TCLAP::ValueArg<String> levelNameArg("", "level-name", "Level name", false, "world", "string", cmd);
    TCLAP::SwitchArg stripLogColorsArg("", "strip-log-colors", "Strip log colors", cmd, false);
    TCLAP::ValueArg<int> maxPlayersArg("", "max-players", "Max players", false, 20, "max-players", cmd);
    TCLAP::SwitchArg noConsoleArg("", "no-console", "Disable console", cmd, false);
    TCLAP::SwitchArg onlineModeArg("", "online-mode", "Enable online mode", cmd, false);
    TCLAP::ValueArg<String> pluginsDirectoryArg("", "plugins-directory", "Plugins directory", false, "", "directory",
                                                cmd);
    TCLAP::ValueArg<String> worldDirArg("", "world-directory", "World directory", false, "", "directory", cmd);
    cmd.parse(argc, argv);

    Settings settings;
    settings.minePlusPlusSettingsFile = minePlusPlusSettingsFileArg.getValue();
    settings.propertiesFile = propertiesFileArg.getValue();
    settings.dateFormat = dateFormatArg.getValue();
    settings.eulaAgree = eulaAgreeArg.getValue();
    settings.fileEncoding = fileEncodingArg.getValue();
    settings.host = hostArg.getValue();
    settings.port = portArg.getValue();
    settings.levelName = levelNameArg.getValue();
    settings.stripLogColors = stripLogColorsArg.getValue();
    settings.maxPlayers = maxPlayersArg.getValue();
    settings.noConsole = noConsoleArg.getValue();
    settings.onlineMode = onlineModeArg.getValue();
    settings.pluginsDirectory = pluginsDirectoryArg.getValue();
    settings.worldDir = worldDirArg.getValue();
    return settings;
}

int RealMain(int argc, char** argv)
{
// Enable ANSI color codes on Windows.
#if defined(MPP_PLATFORM_WINDOWS)
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;
    GetConsoleMode(stdoutHandle, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(stdoutHandle, dwMode);
#endif

    MPP_LOG(LogLevel::Info, "Starting MinePlusPlus version " << MPP_VERSION);

    try
    {
        Settings settings = ParseSettings(argc, argv);
        MinePlusPlus* minePlusPlus = new MinePlusPlus(settings);
        minePlusPlus->StartServer();
        return 0;
    }
    catch (TCLAP::ArgException& e)
    {
        MPP_LOG(LogLevel::Fatal, e.error() << " for arg " << e.argId());
        return 1;
    }
    catch (...)
    {
        MPP_LOG(LogLevel::Fatal, "Unknown exception while starting.");
        return 1;
    }
}
} // namespace mpp