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

// Use string str to easy match str in gtest
void MakeInfoLogEntry(const std::string& fn, const std::string& str);
void MakeWarnLogEntry(const std::string& fn, const std::string& str);
void MakeErrorLogEntry(const std::string& fn, const std::string& str);
void MakeDebugLogEntry(const std::string& fn, const std::string& str);

}  // namespace Tile

}  // namespace FA

#define LOG_TMXINFO(...) FA::Tile::MakeInfoLogEntry(__FUNCTION__, FA::Util::ToString(__VA_ARGS__))
#define LOG_TMXWARN(...) FA::Tile::MakeWarnLogEntry(__FUNCTION__, FA::Util::ToString(__VA_ARGS__))
#define LOG_TMXERROR(...) FA::Tile::MakeErrorLogEntry(__FUNCTION__, FA::Util::ToString(__VA_ARGS__))
#define LOG_TMXDEBUG(...) FA::Tile::MakeDebugLogEntry(__FUNCTION__, FA::Util::ToString(__VA_ARGS__))
