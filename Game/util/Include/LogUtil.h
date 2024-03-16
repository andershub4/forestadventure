/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace LogLib {

class BasicLogger;

}  // namespace LogLib

namespace FA {

void MakeDebugLogEntry(LogLib::BasicLogger& logger, const std::string& fn, const std::string& str);
void MakeInfoLogEntry(LogLib::BasicLogger& logger, const std::string& fn, const std::string& str);
void MakeWarnLogEntry(LogLib::BasicLogger& logger, const std::string& fn, const std::string& str);
void MakeErrorLogEntry(LogLib::BasicLogger& logger, const std::string& fn, const std::string& str);

}  // namespace FA
