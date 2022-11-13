/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Mock/LoggerMock.h"

namespace FA {

namespace Tile {

class LoggerMockProxy
{
public:
    LoggerMockProxy(LogLib::LoggerMock& mock);
    ~LoggerMockProxy();

    LogLib::BasicLogger& GetLog();

private:
    LogLib::LoggerMock& mock_;
};

LogLib::BasicLogger& TmxLog();

}  // namespace Tile

}  // namespace FA
