// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

#include <algorithm>
#include <cctype>

namespace mpp
{
class EDifficulty
{
  public:
    static MPP_API EDifficulty* Peaceful;
    static MPP_API EDifficulty* Easy;
    static MPP_API EDifficulty* Normal;
    static MPP_API EDifficulty* Hard;
    static MPP_API EDifficulty** Values;

    MPP_API EDifficulty(int id, const String& name);

    int m_id;
    String m_name;

    static EDifficulty* ByName(String name)
    {
        std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
        for (int i = 0; i < 4; i++)
        {
            if (name == Values[i]->m_name)
            {
                return Values[i];
            }
        }
        return nullptr;
    }
};

} // namespace mpp