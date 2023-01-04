/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Logging.h"
#include "Folder.h"

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

}  // namespace FA
