/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Util {

class BasicLogger;

void MakeDebugLogEntry(BasicLogger& logger, const std::string& fn, const std::string& str);
void MakeInfoLogEntry(BasicLogger& logger, const std::string& fn, const std::string& str);
void MakeWarnLogEntry(BasicLogger& logger, const std::string& fn, const std::string& str);
void MakeErrorLogEntry(BasicLogger& logger, const std::string& fn, const std::string& str);

}  // namespace Util

}  // namespace FA
