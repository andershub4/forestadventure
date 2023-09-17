/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

namespace FA {

namespace Tile {

class LoggerMock
{
public:
    LoggerMock() { instance_ = this; }
    ~LoggerMock() { instance_ = nullptr; }

    LoggerMock(const LoggerMock&) = delete;
    LoggerMock& operator=(const LoggerMock&) = delete;
    LoggerMock(LoggerMock&&) = delete;
    LoggerMock& operator=(LoggerMock&&) = delete;

    static LoggerMock& Instance() { return *instance_; }

    MOCK_METHOD(void, OpenLog, (const std::string& folder, const std::string& fileName, bool toConsole));
    MOCK_METHOD(void, CloseLog, ());
    MOCK_METHOD(void, MakeDebugLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeInfoLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeWarnLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeErrorLogEntry, (const std::string& str));

private:
    static LoggerMock* instance_;
};

}  // namespace Tile

}  // namespace FA