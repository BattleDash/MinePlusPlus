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

// These are a mess purely because of clang-format. I apologize to your eyes.
// We need this because we can't use X Macros for LogLevel (#level), or else the output will be "LogLevel::Info", instead of just "Info".
// If you have a better solution, feel free to make a PR or an issue.
#define MPP_LOG_LEVEL_TO_STRING(level)                                                                                 \
    (level == mpp::LogLevel::Debug                                                                                     \
         ? "Debug"                                                                                                     \
         : (level == mpp::LogLevel::Info                                                                               \
                ? "Info"                                                                                               \
                : (level == mpp::LogLevel::Warning                                                                     \
                       ? "Warning"                                                                                     \
                       : (level == mpp::LogLevel::Error ? "Error"                                                      \
                                                        : (level == mpp::LogLevel::Fatal ? "Fatal" : "Unknown")))))

#define MPP_LOG_LEVEL_COLOR(level)                                                                                     \
    (level == mpp::LogLevel::Debug                                                                                     \
         ? "\x1B[34m"                                                                                                  \
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
                       << "[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] [" << MPP_LOG_LEVEL_TO_STRING(level)        \
                       << "] [" << __FILE__ << ":" << __LINE__ << "] " << message << "\x1B[0m");                       \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        STREAM_MESSAGE(MPP_LOG_LEVEL_COLOR(level)                                                                      \
                       << "[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] [" << MPP_LOG_LEVEL_TO_STRING(level)        \
                       << "] [" << __FUNCTION__ << "] " << message << "\x1B[0m");                                      \
    }

#define MPP_LOG_INTERNAL(level, message)                                                                               \
    STREAM_MESSAGE(MPP_LOG_LEVEL_COLOR(level) << "[MinePlusPlus-" << MPP_BUILD_CHANNEL_NAME << "] ["                   \
                                              << MPP_LOG_LEVEL_TO_STRING(level) << "] " << message << "\x1B[0m");

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