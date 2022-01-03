// Copyright BattleDash. All Rights Reserved.

#include <World/EDifficulty.h>

namespace mpp
{
EDifficulty::EDifficulty(int id, const String& name) : m_id(id), m_name(name)
{
}

EDifficulty* EDifficulty::Peaceful = new EDifficulty(0, "peaceful");
EDifficulty* EDifficulty::Easy = new EDifficulty(1, "easy");
EDifficulty* EDifficulty::Normal = new EDifficulty(2, "normal");
EDifficulty* EDifficulty::Hard = new EDifficulty(3, "hard");
} // namespace mpp