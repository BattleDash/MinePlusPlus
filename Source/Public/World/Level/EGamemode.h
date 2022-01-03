// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

#include <algorithm>
#include <cctype>

namespace mpp
{
class EGamemode
{
  public:
    static MPP_API EGamemode* Survival;
    static MPP_API EGamemode* Creative;
    static MPP_API EGamemode* Adventure;
    static MPP_API EGamemode* Spectator;
    static MPP_API EGamemode** Values;

    MPP_API EGamemode(int id, const String& name);

    int m_id;
    String m_name;

    static EGamemode* ByName(String name)
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