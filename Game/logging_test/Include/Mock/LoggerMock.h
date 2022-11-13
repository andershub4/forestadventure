/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicLogger.h"

namespace LogLib {

class LoggerMock : public BasicLogger
{
public:
    MOCK_METHOD(void, OpenLog, (const std::string& folder, const std::string& fileName, bool toConsole), (override));
    MOCK_METHOD(void, CloseLog, (), (override));
    MOCK_METHOD(void, MakeLogEntry,
                (const BasicLogger::LogLevel& logLevel, const std::string& func, const std::string& logStr),
                (override));
};

}  // namespace LogLib
