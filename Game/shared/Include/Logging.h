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

LogLib::BasicLogger& Logger();

}  // namespace Shared

}  // namespace FA

#define LOG_INFO(...) FA::MakeInfoLogEntry(FA::Shared::Logger(), __FUNCTION__, FA::ToString(__VA_ARGS__))
#define LOG_WARN(...) FA::MakeWarnLogEntry(FA::Shared::Logger(), __FUNCTION__, FA::ToString(__VA_ARGS__))
#define LOG_ERROR(...) FA::MakeErrorLogEntry(FA::Shared::Logger(), __FUNCTION__, FA::ToString(__VA_ARGS__))
#define LOG_DEBUG(...) FA::MakeDebugLogEntry(FA::Shared::Logger(), __FUNCTION__, FA::ToString(__VA_ARGS__))

#define LOG_INFO_ENTER_FUNC() FA::MakeInfoLogEntry(FA::Shared::Logger(), __FUNCTION__, "ENTER")
#define LOG_INFO_EXIT_FUNC() FA::MakeInfoLogEntry(FA::Shared::Logger(), __FUNCTION__, "EXIT")
