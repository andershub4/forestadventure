/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TmxLogging.h"

#include "Folder.h"
#include "Logger.h"

namespace FA {

namespace Tile {

LogLib::BasicLogger& TmxLog()
{
    static LogLib::Logger tmxLog;

    static bool once = []() {
        tmxLog.OpenLog(FA::GetLogPath(), "tmx-log.txt", false);
        return true;
    }();

    return tmxLog;
}

void MakeDebugLogEntry(const std::string& fn, const std::string& str)
{
    TmxLog().MakeDebugLogEntry(fn, str);
}

void MakeInfoLogEntry(const std::string& fn, const std::string& str)
{
    TmxLog().MakeInfoLogEntry(fn, str);
}

void MakeWarnLogEntry(const std::string& fn, const std::string& str)
{
    TmxLog().MakeWarnLogEntry(fn, str);
}

void MakeErrorLogEntry(const std::string& fn, const std::string& str)
{
    TmxLog().MakeErrorLogEntry(fn, str);
}

}  // namespace Tile

}  // namespace FA
