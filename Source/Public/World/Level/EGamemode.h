// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>

#include <algorithm>
#include <cctype>

namespace mpp
{
class EGamemode
{
  public:
    static EGamemode* Survival;
    static EGamemode* Creative;
    static EGamemode* Adventure;
    static EGamemode* Spectator;

    EGamemode(int id, const String& name);

    int m_id;
    String m_name;

    inline const String ToString()
    {
        if (m_id == EGamemode::Survival->m_id)
        {
            return "survival";
        }
        else if (m_id == EGamemode::Creative->m_id)
        {
            return "creative";
        }
        else if (m_id == EGamemode::Adventure->m_id)
        {
            return "adventure";
        }
        else if (m_id == EGamemode::Spectator->m_id)
        {
            return "spectator";
        }
        else
        {
            return "unknown";
        }
    }

    static EGamemode* ByName(String name)
    {
        std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
        if (name == "survival")
        {
            return EGamemode::Survival;
        }
        else if (name == "creative")
        {
            return EGamemode::Creative;
        }
        else if (name == "adventure")
        {
            return EGamemode::Adventure;
        }
        else if (name == "spectator")
        {
            return EGamemode::Spectator;
        }
        else
        {
            return nullptr;
        }
    }
};

} // namespace mpp