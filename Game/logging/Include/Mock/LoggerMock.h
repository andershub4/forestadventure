/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

namespace LogLib {

// Currently not used. LoggerMocks in Shared and Tile projects
// redefine the MOCK_METHODS, so test projects that uses
// the LoggerMocks does not need to add include paths to
// logging project as well.
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

}  // namespace LogLib
