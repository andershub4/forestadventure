/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Logging.h"

#include "Folder.h"
#include "Logger.h"

namespace FA {

LogLib::Logger& MainLog()
{
    static LogLib::Logger mainLog;

    static bool once = []() {
        mainLog.OpenLog(FA::GetLogPath(), "log.txt", true);
        return true;
    }();

    return mainLog;
}

void MakeDebugLogEntry(const std::string& fn, const std::string& str)
{
    MainLog().MakeDebugLogEntry(fn, str);
}

void MakeInfoLogEntry(const std::string& fn, const std::string& str)
{
    MainLog().MakeInfoLogEntry(fn, str);
}

void MakeWarnLogEntry(const std::string& fn, const std::string& str)
{
    MainLog().MakeWarnLogEntry(fn, str);
}

void MakeErrorLogEntry(const std::string& fn, const std::string& str)
{
    MainLog().MakeErrorLogEntry(fn, str);
}

}  // namespace FA
