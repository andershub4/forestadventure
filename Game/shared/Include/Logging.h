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

Util::LoggerIf& Logger();

}  // namespace Shared

}  // namespace FA

#define LOG_INFO(...) Util::MakeInfoLogEntry(Shared::Logger(), __FUNCTION__, Util::ToString(__VA_ARGS__))
#define LOG_WARN(...) Util::MakeWarnLogEntry(Shared::Logger(), __FUNCTION__, Util::ToString(__VA_ARGS__))
#define LOG_ERROR(...) Util::MakeErrorLogEntry(Shared::Logger(), __FUNCTION__, Util::ToString(__VA_ARGS__))
#define LOG_DEBUG(...) Util::MakeDebugLogEntry(Shared::Logger(), __FUNCTION__, Util::ToString(__VA_ARGS__))

#define LOG_INFO_ENTER_FUNC() Util::MakeInfoLogEntry(Shared::Logger(), __FUNCTION__, "ENTER")
#define LOG_INFO_EXIT_FUNC() Util::MakeInfoLogEntry(Shared::Logger(), __FUNCTION__, "EXIT")
