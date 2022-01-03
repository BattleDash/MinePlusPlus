// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/String.h>

namespace mpp
{
    enum class EDifficulty
    {
        Peaceful,
        Easy,
        Normal,
        Hard
    };

    inline const String ToString(EDifficulty difficulty)
    {
        switch (difficulty)
        {
        case EDifficulty::Peaceful:
            return "peaceful";
        case EDifficulty::Easy:
            return "easy";
        case EDifficulty::Normal:
            return "normal";
        case EDifficulty::Hard:
            return "hard";
        default:
            return "unknown";
        }
    }

    inline EDifficulty ByName(const String& name)
    {
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



}