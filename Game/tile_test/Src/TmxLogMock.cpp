/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Mock/TmxLogMock.h"

namespace FA {

namespace Tile {

namespace {

LoggerMockProxy* gMock_ = nullptr;

}  // namespace

LogLib::BasicLogger& TmxLog()
{
    if (gMock_) {
        return gMock_->GetLog();
    }

    static LogLib::LoggerMock defaultMock;
    return defaultMock;
}

LoggerMockProxy::LoggerMockProxy(LogLib::LoggerMock& mock)
    : mock_(mock)
{
    gMock_ = this;
}

LoggerMockProxy::~LoggerMockProxy()
{
    gMock_ = nullptr;
}

LogLib::BasicLogger& LoggerMockProxy::GetLog()
{
    return mock_;
}

}  // namespace Tile

}  // namespace FA
