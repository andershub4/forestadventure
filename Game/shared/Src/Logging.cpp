/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Logging.h"

#include "Folder.h"
#include "Logger.h"

namespace {

FA::Util::LoggerIf& Logger()
{
    static FA::Util::Logger logger;

    static bool once = []() {
        logger.OpenLog(FA::Util::GetLogPath(), "log.txt", true);
        return true;
    }();

    return logger;
}

}  // namespace

namespace FA {

namespace Shared {

// Implementation must be in a cpp file, so it can be substituted during link time
// for mocking purpose
void MakeDebugLogEntry(const std::string& fn, const std::string& str)
{
    Logger().MakeDebugLogEntry(fn, str);
}

void MakeInfoLogEntry(const std::string& fn, const std::string& str)
{
    Logger().MakeInfoLogEntry(fn, str);
}

void MakeWarnLogEntry(const std::string& fn, const std::string& str)
{
    Logger().MakeWarnLogEntry(fn, str);
}

void MakeErrorLogEntry(const std::string& fn, const std::string& str)
{
    Logger().MakeErrorLogEntry(fn, str);
}

}  // namespace Shared

}  // namespace FA
