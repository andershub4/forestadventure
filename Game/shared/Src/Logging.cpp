/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Logging.h"

#include "Folder.h"
#include "Logger.h"

namespace FA {

namespace Shared {

// Implementation must be in a cpp file, so it can be substituted during link time
// for mocking purpose
LogLib::BasicLogger& Logger()
{
    static LogLib::Logger logger;

    static bool once = []() {
        logger.OpenLog(FA::GetLogPath(), "log.txt", true);
        return true;
    }();

    return logger;
}

}  // namespace Shared

}  // namespace FA
