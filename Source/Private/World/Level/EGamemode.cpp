// Copyright BattleDash. All Rights Reserved.

#include <World/Level/EGamemode.h>

namespace mpp
{
EGamemode::EGamemode(int id, const String& name) : m_id(id), m_name(name)
{
}

EGamemode* EGamemode::Survival = new EGamemode(0, "survival");
EGamemode* EGamemode::Creative = new EGamemode(1, "creative");
EGamemode* EGamemode::Adventure = new EGamemode(2, "adventure");
EGamemode* EGamemode::Spectator = new EGamemode(3, "spectator");
} // namespace mpp