/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Mock/TmxLogMock.h"

namespace FA {

namespace Tile {

namespace {

StaticLogMock* gMock_ = nullptr;

}  // namespace

LogLib::BasicLogger& TmxLog()
{
    return gMock_->GetLog();
}

StaticLogMock::StaticLogMock(LogLib::LoggerMock& mock)
    : mockProxy_(mock)
{
    gMock_ = this;
}

StaticLogMock::~StaticLogMock()
{
    gMock_ = nullptr;
}

LogLib::LoggerMockProxy& StaticLogMock::GetLog()
{
    return mockProxy_;
}

}  // namespace Tile

}  // namespace FA
