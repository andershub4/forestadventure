/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "Mock/BasicLoggerMock.h"

namespace FA {

namespace Tile {

class LoggerMock : public Util::BasicLoggerMock
{
public:
    LoggerMock() { instance_ = this; }
    ~LoggerMock() { instance_ = nullptr; }
    static LoggerMock& Instance() { return *instance_; }

private:
    static LoggerMock* instance_;
};

}  // namespace Tile

}  // namespace FA
