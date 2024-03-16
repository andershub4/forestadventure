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

// Implementation must be in a cpp file, so it can be substituted during link time
// for mocking purpose
BasicLogger& Logger()
{
    static FA::Logger logger;

    static bool once = []() {
        logger.OpenLog(FA::GetLogPath(), "tmx-log.txt", false);
        return true;
    }();

    return logger;
}

}  // namespace Tile

}  // namespace FA
