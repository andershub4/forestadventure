/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#ifndef FA_UNITTEST
#include "Logger.h"

namespace FA {

LogLib::Logger& TmxLog();

}  // namespace FA

#define LOG_TMXINFO(...) FA::TmxLog().MakeLogEntry(LogLib::Logger::LogLevel::Info, __FUNCTION__, __VA_ARGS__)
#define LOG_TMXWARN(...) FA::TmxLog().MakeLogEntry(LogLib::Logger::LogLevel::Warning, __FUNCTION__, __VA_ARGS__)
#define LOG_TMXERROR(...) FA::TmxLog().MakeLogEntry(LogLib::Logger::LogLevel::Error, __FUNCTION__, __VA_ARGS__)

#else
#define LOG_TMXINFO(...)
#define LOG_TMXWARN(...)
#define LOG_TMXERROR(...)
#endif
