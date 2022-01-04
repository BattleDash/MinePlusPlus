// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Core/Eula.h>
#include <Util/PropertiesFormat.h>

namespace mpp
{
Eula::Eula(const String& filePath) : m_accepted(false)
{
    Properties properties = Properties(filePath);
    m_accepted = properties.GetValue<bool>("eula", false);
    if (!properties.IsLoaded())
    {
        properties.AddComment("By changing the setting below to TRUE you are indicating your agreement to the Minecraft EULA (https://account.mojang.com/documents/minecraft_eula).");
        properties.Save();
    }
}
} // namespace mpp