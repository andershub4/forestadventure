/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Mock/LoggerMock.h"

namespace FA {

// To follow existing naming convention, this namespace
// should be called TestCommon.
// However, this is not possible, since the production code
// for MakeInfoLogEntry etc. is inside Tile namespace.
// The code for production and test must be within same
// namespace, so link time substition will work.
namespace Tile
{

class LoggerMock : public LogLib::LoggerMock
{
public:
    LoggerMock() { instance_ = this; }
    ~LoggerMock() { instance_ = nullptr; }

    LoggerMock(const LoggerMock&) = delete;
    LoggerMock& operator=(const LoggerMock&) = delete;
    LoggerMock(LoggerMock&&) = delete;
    LoggerMock& operator=(LoggerMock&&) = delete;

    static LoggerMock& Instance() { return *instance_; }

private:
    static LoggerMock* instance_;
};

}  // namespace Tile

}  // namespace FA
