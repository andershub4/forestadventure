/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#ifndef FA_UNITTEST
#include "Logger.h"

#include <sstream>

namespace FA {

namespace Tile {

LogLib::Logger& TmxLog();

}  // namespace Tile

}  // namespace FA

#define LOG_TMXINFO(...) \
    FA::Tile::TmxLog().MakeLogEntry(LogLib::Logger::LogLevel::Info, __FUNCTION__, LogLib::Logger::ToString(__VA_ARGS__))
#define LOG_TMXWARN(...)                                                             \
    FA::Tile::TmxLog().MakeLogEntry(LogLib::Logger::LogLevel::Warning, __FUNCTION__, \
                                    LogLib::Logger::ToString(__VA_ARGS__))
#define LOG_TMXERROR(...)                                                          \
    FA::Tile::TmxLog().MakeLogEntry(LogLib::Logger::LogLevel::Error, __FUNCTION__, \
                                    LogLib::Logger::ToString(__VA_ARGS__))

#define LOG_TMXVARIABLE(variable)                       \
    std::ostringstream oss;                             \
    oss << "{" << #variable << ": " << variable << "}"; \
    FA::Tile::TmxLog().MakeLogEntry(LogLib::Logger::LogLevel::Info, __FUNCTION__, oss.str())

#else
#define LOG_TMXINFO(...)
#define LOG_TMXWARN(...)
#define LOG_TMXERROR(...)
#define LOG_TMXVARIABLE(attr)
#endif
