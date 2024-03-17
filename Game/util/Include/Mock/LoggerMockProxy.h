/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Logger.h"

#include <string>

#include "BasicLoggerMock.h"

namespace FA {

namespace Util {

class LoggerMockProxy : public BasicLogger
{
public:
    LoggerMockProxy(BasicLoggerMock& mock)
        : mock_(mock)
    {}

    virtual void OpenLog(const std::string& folder, const std::string& fileName, bool toConsole) override {}
    virtual void CloseLog() override {}

    virtual void MakeDebugLogEntry(const std::string& fn, const std::string& str) override
    {
        // No need to test debug log
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
    BasicLoggerMock& mock_;
};

}  // namespace Util

}  // namespace FA
