// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>

#include <algorithm>
#include <cctype>

namespace mpp
{
class EDifficulty
{
  public:
    static EDifficulty* Peaceful;
    static EDifficulty* Easy;
    static EDifficulty* Normal;
    static EDifficulty* Hard;

    EDifficulty(int id, const String& name);

    int m_id;
    String m_name;

    inline const String ToString()
    {
        if (m_id == EDifficulty::Peaceful->m_id)
        {
            return "peaceful";
        }
        else if (m_id == EDifficulty::Easy->m_id)
        {
            return "easy";
        }
        else if (m_id == EDifficulty::Normal->m_id)
        {
            return "normal";
        }
        else if (m_id == EDifficulty::Hard->m_id)
        {
            return "hard";
        }
        else
        {
            return "unknown";
        }
    }

    static EDifficulty* ByName(String name)
    {
        std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
        if (name == "peaceful")
        {
            return EDifficulty::Peaceful;
        }
        else if (name == "easy")
        {
            return EDifficulty::Easy;
        }
        else if (name == "normal")
        {
            return EDifficulty::Normal;
        }
        else if (name == "hard")
        {
            return EDifficulty::Hard;
        }
        else
        {
            return EDifficulty::Peaceful;
        }
    }
};

} // namespace mpp