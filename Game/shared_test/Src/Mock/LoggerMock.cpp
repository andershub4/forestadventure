/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Mock/LoggerMock.h"

namespace FA {

namespace Shared {

Util::LoggerIf* LoggerMock::proxy_;

// Implementation must be in a cpp file, so it can be substituted during link time
// for mocking purpose
Util::LoggerIf& Logger()
{
    return LoggerMock::Proxy();
}

}  // namespace Shared

}  // namespace FA
