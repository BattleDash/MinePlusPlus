// Copyright BattleDash. All Rights Reserved.

#pragma once

namespace mpp
{
#if defined(MPP_EXPORTS)
#    if defined(MPP_PLATFORM_WINDOWS)
#        define MPP_API __declspec(dllexport)
#        define MPP_PLUGIN_API __declspec(dllimport)
#    elif defined(MPP_PLATFORM_LINUX)
#        define MPP_API __attribute__((visibility("default")))
#        define MPP_PLUGIN_API
#    endif
#else
#    if defined(MPP_PLATFORM_WINDOWS)
#        define MPP_API __declspec(dllimport)
#        define MPP_PLUGIN_API __declspec(dllexport)
#    elif defined(MPP_PLATFORM_LINUX)
#        define MPP_API 
#        define MPP_PLUGIN_API
#    endif
#endif

#if defined(MPP_PLATFORM_WINDOWS)
#    define MPP_PLATFORM_NAME "Windows"
#elif defined(MPP_PLATFORM_LINUX)
#    define MPP_PLATFORM_NAME "Linux"
#else
#    error "Unknown platform"
#endif

enum class Platform
{
    Windows,
    Linux,

#if defined(MPP_PLATFORM_WINDOWS)
    Current = Windows
#elif defined(MPP_PLATFORM_LINUX)
    Current = Linux
#else
#    error "Unknown platform"
#endif
};

#if defined(MPP_DEBUG)
#    define MPP_BUILD_CHANNEL_NAME "Debug"
#else
#    define MPP_BUILD_CHANNEL_NAME "Release"
#endif

enum class BuildChannel
{
    Debug,
    Release,

#if defined(MPP_DEBUG)
    Current = Debug
#else
    Current = Release
#endif
};
} // namespace mpp