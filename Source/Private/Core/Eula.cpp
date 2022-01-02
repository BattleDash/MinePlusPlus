// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Core/Eula.h>
#include <Util/Properties.h>

namespace mpp
{
Eula::Eula(const String& filePath) : m_accepted(false)
{
    Properties properties = Properties(filePath);
    if (!properties.IsLoaded())
    {
        properties.SetValue("eula", "false");
        properties.Save();
    }
    m_accepted = properties.GetValue<bool>("eula", false);
}

bool Eula::IsAccepted() const
{
    return m_accepted;
}
} // namespace mpp