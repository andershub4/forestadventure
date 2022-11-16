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
    MOCK_METHOD(void, MakeLogEntry, (const LogLib::BasicLogger::LogLevel& logLevel, const std::string& logStr));
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

    virtual void MakeLogEntry(const BasicLogger::LogLevel& logLevel, const std::string& func,
                              const std::string& logStr) override
    {
        mock_.MakeLogEntry(logLevel, logStr);
    }

private:
    LoggerMock& mock_;
};

}  // namespace LogLib
