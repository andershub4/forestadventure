/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Util {

class LoggerIf;

void MakeDebugLogEntry(LoggerIf& logger, const std::string& fn, const std::string& str);
void MakeInfoLogEntry(LoggerIf& logger, const std::string& fn, const std::string& str);
void MakeWarnLogEntry(LoggerIf& logger, const std::string& fn, const std::string& str);
void MakeErrorLogEntry(LoggerIf& logger, const std::string& fn, const std::string& str);

}  // namespace Util

}  // namespace FA
