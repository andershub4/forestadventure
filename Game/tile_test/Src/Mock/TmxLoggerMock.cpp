/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Mock/TmxLoggerMock.h"

namespace FA {

namespace Tile {

BasicLogger* LoggerMock::proxy_;

// Implementation must be in a cpp file, so it can be substituted during link time
// for mocking purpose
BasicLogger& Logger()
{
    return LoggerMock::Proxy();
}

}  // namespace Tile

}  // namespace FA
