/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

namespace FA {

namespace Shared {

class LoggerMock
{
public:
    LoggerMock() { Instance() = this; }
    ~LoggerMock() { Instance() = nullptr; }

    LoggerMock(const LoggerMock&) = delete;
    LoggerMock& operator=(const LoggerMock&) = delete;
    LoggerMock(LoggerMock&&) = delete;
    LoggerMock& operator=(LoggerMock&&) = delete;

    static LoggerMock*& Instance()
    {
        static LoggerMock* mock;
        return mock;
    }

    MOCK_METHOD(void, OpenLog, (const std::string& folder, const std::string& fileName, bool toConsole));
    MOCK_METHOD(void, CloseLog, ());
    MOCK_METHOD(void, MakeDebugLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeInfoLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeWarnLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeErrorLogEntry, (const std::string& str));
};

inline void MakeDebugLogEntry(const std::string& fn, const std::string& str)
{
    // No need to test DebugLogEntry
}

inline void MakeInfoLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance()->MakeInfoLogEntry(str);
}

inline void MakeWarnLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance()->MakeWarnLogEntry(str);
}

inline void MakeErrorLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance()->MakeErrorLogEntry(str);
}

}  // namespace Shared

}  // namespace FA
