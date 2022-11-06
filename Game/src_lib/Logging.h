/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Logger.h"

namespace FA {

LogLib::Logger& MainLog();

}  // namespace FA

#define LOG_INFO(...) \
    FA::MainLog().MakeLogEntry(LogLib::Logger::LogLevel::Info, __FUNCTION__, LogLib::Logger::ToString(__VA_ARGS__))
#define LOG_WARN(...) \
    FA::MainLog().MakeLogEntry(LogLib::Logger::LogLevel::Warning, __FUNCTION__, LogLib::Logger::ToString(__VA_ARGS__))
#define LOG_ERROR(...) \
    FA::MainLog().MakeLogEntry(LogLib::Logger::LogLevel::Error, __FUNCTION__, LogLib::Logger::ToString(__VA_ARGS__))

#define LOG_INFO_ENTER_FUNC() FA::MainLog().MakeLogEntry(LogLib::Logger::LogLevel::Info, __FUNCTION__, "ENTER")
#define LOG_INFO_EXIT_FUNC() FA::MainLog().MakeLogEntry(LogLib::Logger::LogLevel::Info, __FUNCTION__, "EXIT")
