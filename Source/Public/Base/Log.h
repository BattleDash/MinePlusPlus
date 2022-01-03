// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Base/Platform.h>
#include <Base/String.h>

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

    Current = Debug
};

// This is a mess purely because of clang-format.
#define MPP_LOG_LEVEL_COLOR(level)                                                                                     \
    (level == mpp::LogLevel::Debug                                                                                     \
         ? "\x1B[37m"                                                                                                  \
         : (level == mpp::LogLevel::Info                                                                               \
                ? ""                                                                                                   \
                : (level == mpp::LogLevel::Warning                                                                     \
                       ? "\x1B[33m"                                                                                    \
                       : (level == mpp::LogLevel::Error ? "\x1B[31m"                                                   \
                                                        : (level == mpp::LogLevel::Fatal ? "\x1B[31m" : "")))))

#define SHOULD_LOG(level) (level >= mpp::LogLevel::Current)

// We could one-line this, but operator<< here returns an ostream, which doesn't have a str() method, and gcc doesn't
// like that.
#define STREAM_MESSAGE(message)                                                                                        \
    std::stringstream ss;                                                                                              \
    ss << message;                                                                                                     \
    std::cout << ss.str() << std::endl;

#define MPP_LOG_INTERNAL_DEBUG(level, message)                                                                         \
    if (mpp::BuildChannel::Current == mpp::BuildChannel::Debug)                                                        \
    {                                                                                                                  \
        STREAM_MESSAGE(MPP_LOG_LEVEL_COLOR(level)                                                                      \
                       << "[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] [" << #level << "] [" << __FILE__ << ":"    \
                       << __LINE__ << "] " << message << "\x1B[0m");                                                   \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        STREAM_MESSAGE(MPP_LOG_LEVEL_COLOR(level) << "[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] [" << #level     \
                                                  << "] [" << __FUNCTION__ << "] " << message << "\x1B[0m");           \
    }

#define MPP_LOG_INTERNAL(level, message)                                                                               \
    STREAM_MESSAGE(MPP_LOG_LEVEL_COLOR(level)                                                                          \
                   << "[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] [" << #level << "] " << message << "\x1B[0m");

#ifndef MPP_FORCE_DEBUG_LOGS
#    define MPP_FORCE_DEBUG_LOGS 0
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