// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

namespace mpp
{
    class Eula
    {
    public:
        MPP_API Eula(const String& filePath);

        MPP_API bool IsAccepted() const;
    private:
        bool m_accepted;
    };
}