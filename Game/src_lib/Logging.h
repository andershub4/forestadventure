/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Format.h"
#include "Logger.h"

namespace FA {

LogLib::Logger& MainLog();

}  // namespace FA

#define LOG_INFO(...) FA::MainLog().MakeInfoLogEntry(__FUNCTION__, LogLib::Format::ToString(__VA_ARGS__))
#define LOG_WARN(...) FA::MainLog().MakeWarnLogEntry(__FUNCTION__, LogLib::Format::ToString(__VA_ARGS__))
#define LOG_ERROR(...) FA::MainLog().MakeErrorLogEntry(__FUNCTION__, LogLib::Format::ToString(__VA_ARGS__))

#define LOG_INFO_ENTER_FUNC() FA::MainLog().MakeInfoLogEntry(__FUNCTION__, "ENTER")
#define LOG_INFO_EXIT_FUNC() FA::MainLog().MakeInfoLogEntry(__FUNCTION__, "EXIT")
