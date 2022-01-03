// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Core/StartupSettings.h>

int main(int argc, char** argv);

namespace mpp
{
MPP_API StartupSettings ParseSettings(int argc, char** argv);
MPP_API int RealMain(int argc, char** argv);
}