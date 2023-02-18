/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <cstdarg>
#include <string>

#include "Format.h"

namespace FA {

namespace Shared {

void MakeDebugLogEntry(const std::string& fn, const std::string& str);
void MakeInfoLogEntry(const std::string& fn, const std::string& str);
void MakeWarnLogEntry(const std::string& fn, const std::string& str);
void MakeErrorLogEntry(const std::string& fn, const std::string& str);

}  // namespace Shared

}  // namespace FA

#define LOG_INFO(...) FA::Shared::MakeInfoLogEntry(__FUNCTION__, ToString(__VA_ARGS__))
#define LOG_WARN(...) FA::Shared::MakeWarnLogEntry(__FUNCTION__, ToString(__VA_ARGS__))
#define LOG_ERROR(...) FA::Shared::MakeErrorLogEntry(__FUNCTION__, ToString(__VA_ARGS__))

#define LOG_INFO_ENTER_FUNC() FA::Shared::MakeInfoLogEntry(__FUNCTION__, "ENTER")
#define LOG_INFO_EXIT_FUNC() FA::Shared::MakeInfoLogEntry(__FUNCTION__, "EXIT")
