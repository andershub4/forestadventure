/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <cstdarg>
#include <sstream>
#include <string>

#include "Format.h"

namespace FA {

namespace Tile {

void MakeDebugLogEntry(const std::string& fn, const std::string& str);
void MakeInfoLogEntry(const std::string& fn, const std::string& str);
void MakeWarnLogEntry(const std::string& fn, const std::string& str);
void MakeErrorLogEntry(const std::string& fn, const std::string& str);

}  // namespace Tile

}  // namespace FA

#define LOG_TMXINFO(...) MakeInfoLogEntry(__FUNCTION__, ToString(__VA_ARGS__))
#define LOG_TMXWARN(...) MakeWarnLogEntry(__FUNCTION__, ToString(__VA_ARGS__))
#define LOG_TMXERROR(...) MakeErrorLogEntry(__FUNCTION__, ToString(__VA_ARGS__))

#define LOG_TMXVARIABLE(variable)                       \
    std::ostringstream oss;                             \
    oss << "{" << #variable << ": " << variable << "}"; \
    MakeDebugLogEntry(__FUNCTION__, oss.str())
