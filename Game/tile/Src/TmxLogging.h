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

LogLib::BasicLogger& Logger();

}  // namespace Tile

}  // namespace FA

#define LOG_TMXINFO(...) FA::MakeInfoLogEntry(FA::Tile::Logger(), __FUNCTION__, FA::ToString(__VA_ARGS__))
#define LOG_TMXWARN(...) FA::MakeWarnLogEntry(FA::Tile::ogger(), __FUNCTION__, FA::ToString(__VA_ARGS__))
#define LOG_TMXERROR(...) FA::MakeErrorLogEntry(FA::Tile::Logger(), __FUNCTION__, FA::ToString(__VA_ARGS__))
#define LOG_TMXDEBUG(...) FA::MakeDebugLogEntry(FA::Tile::Logger(), __FUNCTION__, FA::ToString(__VA_ARGS__))
