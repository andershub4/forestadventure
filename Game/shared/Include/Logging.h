/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "LogUtil.h"

#include <cstdarg>

#include "Format.h"
#include "Print.h"

namespace FA {

namespace Shared {

// Use string str to easy match str in gtest
void MakeInfoLogEntry(const std::string& fn, const std::string& str);
void MakeWarnLogEntry(const std::string& fn, const std::string& str);
void MakeErrorLogEntry(const std::string& fn, const std::string& str);
void MakeDebugLogEntry(const std::string& fn, const std::string& str);

}  // namespace Shared

}  // namespace FA

#define LOG_INFO(...) FA::Shared::MakeInfoLogEntry(__FUNCTION__, FA::Util::ToString(__VA_ARGS__))
#define LOG_WARN(...) FA::Shared::MakeWarnLogEntry(__FUNCTION__, FA::Util::ToString(__VA_ARGS__))
#define LOG_ERROR(...) FA::Shared::MakeErrorLogEntry(__FUNCTION__, FA::Util::ToString(__VA_ARGS__))
#define LOG_DEBUG(...) FA::Shared::MakeDebugLogEntry(__FUNCTION__, FA::Util::ToString(__VA_ARGS__))

#define LOG_INFO_ENTER_FUNC() FA::Shared::MakeInfoLogEntry(__FUNCTION__, "ENTER")
#define LOG_INFO_EXIT_FUNC() FA::Shared::MakeInfoLogEntry(__FUNCTION__, "EXIT")
