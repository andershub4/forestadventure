/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "LogUtil.h"

#include <cstdarg>

#include "Format.h"
#include "Print.h"

namespace FA {

namespace Tile {

Util::LoggerIf& Logger();

}  // namespace Tile

}  // namespace FA

#define LOG_TMXINFO(...) Util::MakeInfoLogEntry(Tile::Logger(), __FUNCTION__, Util::ToString(__VA_ARGS__))
#define LOG_TMXWARN(...) Util::MakeWarnLogEntry(Tile::ogger(), __FUNCTION__, Util::ToString(__VA_ARGS__))
#define LOG_TMXERROR(...) Util::MakeErrorLogEntry(Tile::Logger(), __FUNCTION__, Util::ToString(__VA_ARGS__))
#define LOG_TMXDEBUG(...) Util::MakeDebugLogEntry(Tile::Logger(), __FUNCTION__, Util::ToString(__VA_ARGS__))
