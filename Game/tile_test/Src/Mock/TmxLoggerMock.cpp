/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Mock/TmxLoggerMock.h"

namespace FA {

namespace Tile {

LoggerMock* LoggerMock::instance_;

void MakeDebugLogEntry(const std::string& fn, const std::string& str)
{
    // No need to test DebugLogEntry
}

void MakeInfoLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance().MakeInfoLogEntry(str);
}

void MakeWarnLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance().MakeWarnLogEntry(str);
}

void MakeErrorLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance().MakeErrorLogEntry(str);
}

}  // namespace Tile

}  // namespace FA
