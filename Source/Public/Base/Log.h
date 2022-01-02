// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

namespace mpp
{
enum class LogLevel
{
    Debug,
    Info,
    Warning,
    Error,
    Fatal,

    Current = Info
};

#define SHOULD_LOG(level) (level >= mpp::LogLevel::Current)

#define STREAM_MESSAGE(message) std::cout << (std::stringstream() << message).str() << std::endl;

#define MPP_LOG_INTERNAL_DEBUG(level, message)                                                                         \
    if (mpp::BuildChannel::Current == mpp::BuildChannel::Debug)                                                        \
    {                                                                                                                  \
        STREAM_MESSAGE("[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] [" << #level << "] [" << __FILE__ << ":"       \
                                        << __LINE__ << "] " << message);                                               \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        STREAM_MESSAGE("[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] [" << #level << "] [" << __FUNCTION__ << "] "  \
                                        << message);                                                                   \
    }

#define MPP_LOG_INTERNAL(level, message)                                                                               \
    STREAM_MESSAGE("[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] [" << #level << "] " << message);

#ifndef MPP_FORCE_DEBUG_LOGS
#define MPP_FORCE_DEBUG_LOGS 0
#endif

#define MPP_LOG(level, message)                                                                                        \
    if (SHOULD_LOG(level))                                                                                             \
    {                                                                                                                  \
        if (level == mpp::LogLevel::Debug || MPP_FORCE_DEBUG_LOGS)                                                     \
        {                                                                                                              \
            MPP_LOG_INTERNAL_DEBUG(level, message);                                                                    \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            MPP_LOG_INTERNAL(level, message);                                                                          \
        }                                                                                                              \
    }
} // namespace mpp