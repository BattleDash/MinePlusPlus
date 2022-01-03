// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>
#include <Plugins/Plugin.h>

namespace mpp
{
class WrappedPlugin
{
  public:
    WrappedPlugin(Plugin* plugin);

    Plugin* m_plugin;
    String m_filePath;
    String m_dataPath;
};
} // namespace mpp