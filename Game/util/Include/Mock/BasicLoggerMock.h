/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include <string>

namespace FA {

namespace Util {

class BasicLoggerMock
{
public:
    BasicLoggerMock() = default;
    virtual ~BasicLoggerMock() = default;
    BasicLoggerMock(const BasicLoggerMock&) = delete;
    BasicLoggerMock& operator=(const BasicLoggerMock&) = delete;
    BasicLoggerMock(BasicLoggerMock&&) = delete;
    BasicLoggerMock& operator=(BasicLoggerMock&&) = delete;

    MOCK_METHOD(void, OpenLog, (const std::string& folder, const std::string& fileName, bool toConsole));
    MOCK_METHOD(void, CloseLog, ());
    MOCK_METHOD(void, MakeDebugLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeInfoLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeWarnLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeErrorLogEntry, (const std::string& str));
};

}  // namespace Util

}  // namespace FA
