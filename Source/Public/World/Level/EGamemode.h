// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>

namespace mpp
{
class EGamemode
{
  public:
    static const EGamemode* Survival;
    static const EGamemode* Creative;
    static const EGamemode* Adventure;
    static const EGamemode* Spectator;

    EGamemode(int id, const String& name) : m_id(id), m_name(name)
    {
    }

    int m_id;
    String m_name;

    inline const String ToString(const EGamemode* difficulty)
    {
        if (difficulty->m_id == EGamemode::Survival->m_id)
        {
            return "survival";
        }
        else if (difficulty->m_id == EGamemode::Creative->m_id)
        {
            return "creative";
        }
        else if (difficulty->m_id == EGamemode::Adventure->m_id)
        {
            return "adventure";
        }
        else if (difficulty->m_id == EGamemode::Spectator->m_id)
        {
            return "spectator";
        }
        else
        {
            return "unknown";
        }
    }

    inline EGamemode* ByName(const String& name)
    {
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
            return EGamemode::Survival;
        }
    }
};

const EGamemode EGamemode::Survival = new EGamemode(0, "survival");
const EGamemode EGamemode::Creative = new EGamemode(1, "creative");
const EGamemode EGamemode::Adventure = new EGamemode(2, "adventure");
const EGamemode EGamemode::Spectator = new EGamemode(3, "spectator");

} // namespace mpp