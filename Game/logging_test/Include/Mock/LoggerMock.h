/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicLogger.h"

namespace LogLib {

class LoggerMock
{
public:
    MOCK_METHOD(void, OpenLog, (const std::string& folder, const std::string& fileName, bool toConsole));
    MOCK_METHOD(void, CloseLog, ());
    MOCK_METHOD(void, MakeDebugLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeInfoLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeWarnLogEntry, (const std::string& str));
    MOCK_METHOD(void, MakeErrorLogEntry, (const std::string& str));
};

class LoggerMockProxy : public LogLib::BasicLogger
{
public:
    LoggerMockProxy(LoggerMock& mock)
        : mock_(mock)
    {}

    virtual void OpenLog(const std::string& folder, const std::string& fileName, bool toConsole) override
    {
        mock_.OpenLog(folder, fileName, toConsole);
    }

    virtual void CloseLog() override { mock_.CloseLog(); }

    virtual void MakeDebugLogEntry(const std::string& fn, const std::string& str) override
    {
        // No need to test DebugLogEntry
    }

    virtual void MakeInfoLogEntry(const std::string& fn, const std::string& str) override
    {
        mock_.MakeInfoLogEntry(str);
    }
    virtual void MakeWarnLogEntry(const std::string& fn, const std::string& str) override
    {
        mock_.MakeWarnLogEntry(str);
    }
    virtual void MakeErrorLogEntry(const std::string& fn, const std::string& str) override
    {
        mock_.MakeErrorLogEntry(str);
    }

private:
    LoggerMock& mock_;
};

}  // namespace LogLib
