/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "Mock/BasicLoggerMock.h"
#include "Mock/LoggerMockProxy.h"

namespace FA {

namespace Shared {

class LoggerMock : public FA::BasicLoggerMock
{
public:
    LoggerMock() { proxy_ = new LoggerMockProxy(*this); }
    ~LoggerMock() { delete proxy_; }

    static BasicLogger& Proxy() { return *proxy_; }

private:
    static BasicLogger* proxy_;
};

}  // namespace Shared

}  // namespace FA
