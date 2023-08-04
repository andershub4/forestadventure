/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Mock/LoggerMock.h"

namespace FA {

namespace Shared {

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

}  // namespace Shared

}  // namespace FA
